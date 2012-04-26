#include "Camera.h"
#include "WPILib.h"
#include "Robotmap.h"
#include "Commands/CameraDefault.h"

float absolute2(float x) {
	if (x < 0) {
		return -x;
	} else
		return x;
}

Camera::Camera() :
  Subsystem("Camera")
{
    AxisCamera &camera = AxisCamera::GetInstance("10.34.99.90");
    camera.WriteResolution(AxisCamera::kResolution_640x480);
    camera.WriteCompression(0);
    camera.GetImage();
  	thresholds[0] = new Threshold(190, 255, 70, 255, 70, 255);
  	thresholds[1] = new Threshold(180, 255, 65, 255, 65, 255);
  	thresholds[2] = new Threshold(170, 255, 60, 255, 60, 255);
  	thresholds[3] = new Threshold(160, 255, 55, 255, 55, 255);
	
}


void Camera::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new CameraDefault());
}

Camera::AngleData Camera::GetAngleData() {
	float halfViewX = 22.5;
	float halfViewY = 16.875;
	AxisCamera &camera = AxisCamera::GetInstance("10.34.99.90");
	printf("Setting Camera Params\n");
	camera.WriteResolution(AxisCamera::kResolution_640x480);
	camera.WriteCompression(0);


	//Threshold threshold2(130, 180, 170, 225, 240, 255);
	//Threshold threshold3(255, 255, 0, 0, 0, 0);
	ColorImage *image;
	image = camera.GetImage();
  if(IS_DEBUG_MODE){
    image->Write("/img/picture.png");
  }
  //  ThresholdRedo:
  vector<ParticleAnalysisReport> *reports = ProcessImageForReport(image,0);

	ParticleAnalysisReport *keeper = NULL;
	bool good[reports->size()];
	for (unsigned int i = 0; i < reports->size(); i++) {
		printf("Testing: Image:%d Width:%d Height:%d State:", i,
				reports->at(i).boundingRect.width,
				reports->at(i).boundingRect.height);
		if (reports->at(i).boundingRect.height >= 80
				&& reports->at(i).boundingRect.width >= 90
				&& reports->at(i).boundingRect.height <= 300
				&& reports->at(i).boundingRect.width <= 350
		//reports->at(i).center_mass_y > 320 && 
		//reports->at(i).center_mass_y < 540 &&
		//reports->at(i).center_mass_x > 140 && 
		//reports->at(i).center_mass_x < 340
		) {
			printf("PASS");
			if (//particle is better than last
			(absolute2(reports->at(i).center_mass_y_normalized) < absolute2(
					keeper->center_mass_y_normalized)) && (absolute2(
					reports->at(i).center_mass_x_normalized) < absolute2(
					keeper->center_mass_x_normalized))) {
				keeper = &reports->at(i);
			}
			good[i] = true;
		} else {
			good[i] = false;
			printf("FAIL ");
		}

	}
	unsigned int count = 0;
	for (unsigned int i = 0; i < reports->size(); i++) {
		count += good[i];
	}

	//The image passed with thresholds, dont need image anymore
	delete image;

	ParticleAnalysisReport *keeps[count];
	count = 0;
	for (unsigned int i = 0; i < reports->size(); i++) {
		if (good[i]) {
			keeps[count] = &reports->at(i);
			count++;
		}
	}

	//No Longer need reports
	delete reports;

	printf("Finding Bottom Rectangle\n");

	//reset keeper to NULL for reuse
	keeper = NULL;

	for (unsigned int i = 0; i < count; i++) {
		ParticleAnalysisReport *report = keeps[i];
		double xNorm = report->center_mass_x_normalized;
		double yNorm = report->center_mass_y_normalized;
		int width = report->boundingRect.width;
		int height = report->boundingRect.height;
		double aspect = (double) width / height;
		printf(
				"\nparticle %d:  center = (%5g,%5g); size = (%3d,%3d); aspect = %g\n",
				report->particleIndex, xNorm, yNorm, width, height, aspect);
		// the rectangle must be wider than minimum fraction of image
		if (width < WIDTH_FRACTION_MIN * report->imageWidth) {
			TEST_MSG("             rectangle is too small\n");
			continue;
		}
		// the bounding rectangle aspect ratio must be within tolerance
		if (aspect < ASPECT_MIN || ASPECT_MAX < aspect) {
			TEST_MSG("             aspect ratio out of tolerance\n");
			continue;
		}
		// the center of the rectangle must be in the bottom of the image
		//SHOULD HAVE TO BE
		//  if ( yNorm >= 0 ) {
		//      TEST_MSG("             center of rectangle is in top of image\n");
		//      continue;
		//  }
		// the center of the rectangle is lower than any before
		if (keeper == NULL || yNorm > keeper->center_mass_y_normalized) {
			keeper = report;
		}
	}

	//print out data about the rectangle that was found
	printf("\nCamera Coords:\n\t\tParticle:Bottom\n\t\tx:%f\n\t\ty:%f\n",
			halfViewX * keeper->center_mass_x_normalized,
			halfViewY * keeper->center_mass_y_normalized);

	ParticleAnalysisReport *bottom = keeper;
	ParticleAnalysisReport *middle1 = 0;
	ParticleAnalysisReport *middle2 = 0;
	double bottomWidth = 2.0 * bottom->boundingRect.width / bottom->imageHeight;
	double bottomHeight = 2.0 * bottom->boundingRect.height
			/ bottom->imageWidth;
	TEST_MSG("bottom: width = %3g; height = %3g\n",bottomWidth,bottomHeight);
	double xLeft = bottom->center_mass_x_normalized - bottomWidth * 0.5;
	double xRight = bottom->center_mass_x_normalized + bottomWidth * 0.5;
	double yMin = bottom->center_mass_y_normalized + bottomHeight * 1.5;
	for (unsigned int i = 0; i < count; i++) {
		ParticleAnalysisReport &report = *keeps[i];
		if (report.particleIndex == bottom->particleIndex) {
			continue;
		}
		double y = report.center_mass_y_normalized;
		double x = report.center_mass_x_normalized;
		// the center of the rectangle must be far enough above the bottom one
		if (y > yMin) {
			TEST_MSG("             center of rectangle is too low\n");
			continue;
		}
		// the rectangle must not be centered over the bottom one
		if (xLeft < x && x < xRight) {
			TEST_MSG("             center of rectangle is too centered\n");
			continue;
		}
		if (middle1 == 0) {
			middle1 = &report;
		} else if (middle2 == 0) {
			middle2 = &report;
		}
	}
	if (middle1) {
		printf("\nCamera Coords:\n\t\tParticle:Middle1\n\t\tx:%f\n\t\ty:%f\n",
				halfViewX * middle1->center_mass_x_normalized,
				halfViewY * middle1->center_mass_y_normalized);
		if (middle2) {
			printf(
					"\nCamera Coords:\n\t\tParticle:Middle2\n\t\tx:%f\n\t\ty:%f\n",
					halfViewX * middle2->center_mass_x_normalized,
					halfViewY * middle2->center_mass_y_normalized);
			// pick the larger of the two because it's closer
			if (middle2->boundingRect.width > middle1->boundingRect.width) {
				middle1 = middle2;
			}
		}
	}

	printf(
			"\nCamera Coords:\n\t\tParticle:The Chosen One\n\t\tx:%f\n\t\ty:%f\n",
			halfViewX * middle1->center_mass_x_normalized,
			halfViewY * middle1->center_mass_y_normalized);
	float x = middle1->center_mass_x_normalized * halfViewX;
	float y = middle1->center_mass_y_normalized * halfViewY;
	FILE *fp2 = CommandBase::GetOIInstance()->fp;
	fprintf(fp2, "X:%f\n Y:%f\n", x, y);
	printf("PARTICLE: X:%f, Y:%f                        ", x, y);
	AngleData a = { x, y };
	return a;
}

ParticleAnalysisReport* Camera::FindBottomRectangle(
		ParticleAnalysisReport *reports[], unsigned int reportCount) {//no & because its a class right?
	TEST_MSG("\nFindBottomRectangle(reports)\n");
	ParticleAnalysisReport *bottom = NULL;

	for (unsigned int i = 0; i < reportCount; i++) {
		ParticleAnalysisReport *report = reports[i];
		double xNorm = report->center_mass_x_normalized;
		double yNorm = report->center_mass_y_normalized;
		int width = report->boundingRect.width;
		int height = report->boundingRect.height;
		double aspect = (double) width / height;
		printf(
				"\nparticle %d:  center = (%5g,%5g); size = (%3d,%3d); aspect = %g\n",
				report->particleIndex, xNorm, yNorm, width, height, aspect);
		// the rectangle must be wider than minimum fraction of image
		if (width < WIDTH_FRACTION_MIN * report->imageWidth) {
			TEST_MSG("             rectangle is too small\n");
			continue;
		}
		// the bounding rectangle aspect ratio must be within tolerance
		if (aspect < ASPECT_MIN || ASPECT_MAX < aspect) {
			TEST_MSG("             aspect ratio out of tolerance\n");
			continue;
		}
		// the center of the rectangle must be in the bottom of the image
		//SHOULD HAVE TO BE
		if (yNorm >= 0) {
			TEST_MSG("             center of rectangle is in top of image\n");
			continue;
		}
		// the center of the rectangle is lower than any before
		if (bottom == 0 || yNorm < bottom->center_mass_y_normalized) {
			bottom = report;
		}
	}
	return bottom;
}

ParticleAnalysisReport* findBottomRectangle(
		vector<ParticleAnalysisReport> reports) {//no & because its a class right?
	TEST_MSG("\nfindBottomRectangle(reports)\n");
	ParticleAnalysisReport *bottom = NULL;
	vector<ParticleAnalysisReport>::iterator it;

	for (it = reports.begin(); it < reports.end(); it++) {
		ParticleAnalysisReport &report = *it;
		double xNorm = report.center_mass_x_normalized;
		double yNorm = report.center_mass_y_normalized;
		int width = report.boundingRect.width;
		int height = report.boundingRect.height;
		double aspect = (double) width / height;
		printf(
				"\nparticle %d:  center = (%5g,%5g); size = (%3d,%3d); aspect = %g\n",
				report.particleIndex, xNorm, yNorm, width, height, aspect);
		// the rectangle must be wider than minimum fraction of image
		if (width < WIDTH_FRACTION_MIN * report.imageWidth) {
			TEST_MSG("             rectangle is too small\n");
			continue;
		}
		// the bounding rectangle aspect ratio must be within tolerance
		if (aspect < ASPECT_MIN || ASPECT_MAX < aspect) {
			TEST_MSG("             aspect ratio out of tolerance\n");
			continue;
		}
		// the center of the rectangle must be in the bottom of the image
		if (yNorm >= 0) {
			TEST_MSG("             center of rectangle is in top of image\n");
			continue;
		}
		// the center of the rectangle is lower than any before
		if (bottom == 0 || yNorm < bottom->center_mass_y_normalized) {
			bottom = &report;
		}
	}
	return bottom;
}

ParticleAnalysisReport* findMiddleRectangle(
		vector<ParticleAnalysisReport>& reports, int bottomIndex) {
	TEST_MSG("\nfindMiddleRectangle(reports,%d)\n",bottomIndex);
	ParticleAnalysisReport& bottom = reports.at(bottomIndex);
	ParticleAnalysisReport* middle1 = 0;
	ParticleAnalysisReport* middle2 = 0;
	vector<ParticleAnalysisReport>::iterator it;
	double bottomWidth = 2.0 * bottom.boundingRect.width / bottom.imageHeight;
	double bottomHeight = 2.0 * bottom.boundingRect.height / bottom.imageHeight;
	TEST_MSG("bottom: width = %3g; height = %3g\n",bottomWidth,bottomHeight);
	double xLeft = bottom.center_mass_x_normalized - bottomWidth * 0.5;
	double xRight = bottom.center_mass_x_normalized + bottomWidth * 0.5;
	double yMin = bottom.center_mass_y_normalized + bottomHeight * 1.5;
	for (it = reports.begin(); it < reports.end(); it++) {
		ParticleAnalysisReport& report = *it;
		if (report.particleIndex == bottomIndex) {
			continue;
		}
		//if ( !acceptableRectangle(report) ) {
		//    continue;
		// }
		double y = report.center_mass_y_normalized;
		double x = report.center_mass_x_normalized;
		// the center of the rectangle must be far enough above the bottom one
		if (y < yMin) {
			TEST_MSG("             center of rectangle is too low\n");
			continue;
		}
		// the rectangle must not be centered over the bottom one
		if (xLeft < x && x < xRight) {
			TEST_MSG("             center of rectangle is too centered\n");
			continue;
		}
		if (middle1 == 0) {
			middle1 = &report;
		} else if (middle2 == 0) {
			middle2 = &report;
		}
	}
	if (middle1) {
		if (middle2) {
			// pick the larger of the two because it's closer
			if (middle2->boundingRect.width > middle1->boundingRect.width) {
				middle1 = middle2;
			}
		}
	}
	return middle1;
}

/* *\ 
 * Get the particle analysis report with a threshold.
 * args: which threshold to USE 0-3 NOT 4
\* */
vector<ParticleAnalysisReport> *Camera::ProcessImageForReport(ColorImage *image,int whatThreshold) {

  printf("Analizing the image with threshold %d\n", whatThreshold);
  
  BinaryImage *thresholdImage = image->ThresholdRGB(*(thresholds[whatThreshold])); // get just the red target pixels
  printf("Threshold Written\n");
  
  BinaryImage *bigObjectsImage = thresholdImage->RemoveSmallObjects(false, 4); // remove small objects (noise)
  printf("Big Objects Written\n");
  
  BinaryImage *convexHullImage = bigObjectsImage->ConvexHull(false); // fill in partial and full rectangles
  printf("Convex Hull Written\n");
  
  ParticleFilterCriteria2 criteria[] = { { IMAQ_MT_BOUNDING_RECT_WIDTH, 30,
			400, false, false }, { IMAQ_MT_BOUNDING_RECT_HEIGHT, 40, 400,
			false, false } };
  
  BinaryImage *filteredImage = convexHullImage->ParticleFilter(criteria, 2); // find the rectangles
  printf("Filtered Image Written\n");
  
  if(IS_DEBUG_MODE){
    char filenames[4][16];
    sprintf(filenames[0], "/img/%dimg1.png", whatThreshold);
    sprintf(filenames[1], "/img/%dimg2.png", whatThreshold);
    sprintf(filenames[2], "/img/%dimg3.png", whatThreshold);
    sprintf(filenames[3], "/img/%dimg4.png", whatThreshold);
    thresholdImage->Write(filenames[0]);
    bigObjectsImage->Write(filenames[1]);
    convexHullImage->Write(filenames[2]);
    filteredImage->Write(filenames[3]);
  }
  
  delete convexHullImage;
  delete bigObjectsImage;
  delete thresholdImage;
  vector<ParticleAnalysisReport> *reports = filteredImage->GetOrderedParticleAnalysisReports();
  delete filteredImage;
  /* Returning the finalized reports */
  return reports;
}
