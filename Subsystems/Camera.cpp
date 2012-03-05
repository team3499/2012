#include "Camera.h"
#include "WPILib.h"
#include "Robotmap.h"
#include "Commands/CameraDefault.h"

float absolute2(float x){
	if(x < 0){return -x;}
	else return x;
}

Camera::Camera() : Subsystem("Camera"){
	AxisCamera &camera = AxisCamera::GetInstance("10.34.99.90");
	camera.WriteResolution(AxisCamera::kResolution_640x480);
	camera.WriteCompression(0);
	camera.GetImage();
}

void Camera::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new CameraDefault());
}

Camera::AngleData Camera::GetAngleData(){
	AxisCamera &camera = AxisCamera::GetInstance("10.34.99.90");
	printf("Setting Camera Params\n");
	camera.WriteResolution(AxisCamera::kResolution_640x480);
	camera.WriteCompression(0);
	
	Thresh thresh = {new Threshold(240, 255, 160, 255, 160, 255),//starting
			         new Threshold(10,  5,   10,  5,   10,  5),//change by this much
			         new Threshold(128, 255, 128, 255, 128, 255),//not more/less than this
			         0};
	Threshold threshold2(130, 180, 170, 225, 240, 255);
	//Threshold threshold3(255, 255, 0, 0, 0, 0);
	ColorImage *image;
	image = camera.GetImage();
	image->Write("/img/0picture.png");
	ThresholdRedo:
	
	ParticleFilterCriteria2 criteria[] = {
		{IMAQ_MT_BOUNDING_RECT_WIDTH, 30, 400, false, false},
		{IMAQ_MT_BOUNDING_RECT_HEIGHT, 40, 400, false, false}
	};
	char filenames[5][16];
	sprintf(filenames[0],"/img/%dimg1.png",thresh.counter);
	sprintf(filenames[1],"/img/%dimg2.png",thresh.counter);
	sprintf(filenames[2],"/img/%dimg3.png",thresh.counter);
	sprintf(filenames[3],"/img/%dimg4.png",thresh.counter);
	sprintf(filenames[4],"/img/%dimg5.png",thresh.counter);
	
	/*new RGBImage("/img/testImage2.bmp")*/;	// get the sample image from the cRIO flash

	printf("Start Image Loaded\n");
	BinaryImage *thresholdImage = image->ThresholdRGB(*(thresh.threshold));	// get just the red target pixels
	thresholdImage -> Write(filenames[1]);
	printf("Threshold Written\n");
	BinaryImage *bigObjectsImage = thresholdImage->RemoveSmallObjects(false, 10);  // remove small objects (noise)
	bigObjectsImage -> Write(filenames[2]);
	printf("Big Objects Written\n");
	BinaryImage *convexHullImage = bigObjectsImage->ConvexHull(false);  // fill in partial and full rectangles
	convexHullImage -> Write(filenames[3]);
	printf("Convex Hull Written\n");
	BinaryImage *filteredImage = convexHullImage->ParticleFilter(criteria, 2);  // find the rectangles
	filteredImage -> Write(filenames[4]);
	printf("Filtered Image Written\n");
	vector<ParticleAnalysisReport> *reports = filteredImage->GetOrderedParticleAnalysisReports();
	delete filteredImage;
	delete convexHullImage;
	delete bigObjectsImage;
	delete thresholdImage;
	particleCount = reports->size();
	
	//printf("\nParticles: %d\n", reports->size());
	
	//if r->area > 3000 && r->height > 80 && r->width > 90 {GOOD RECTANGLE!}
	if(!reports->size()){
		if(thresh.counter < 3){
			FixThreshold(&thresh);
			printf("message0");
			goto ThresholdRedo;
			//rerun filtering with different specs.
		}
	}
	
	ParticleAnalysisReport *keeper = NULL;
	for (unsigned int i = 0; i < reports->size(); i++){
		printf("Testing: Image:%d Width:%d Height:%d State:",i,reports->at(i).boundingRect.width,reports->at(i).boundingRect.height);
		if(reports->at(i).boundingRect.height >= 80 && 
		  reports->at(i).boundingRect.width >= 90 && 
		  reports->at(i).boundingRect.height <= 300 && 
		  reports->at(i).boundingRect.width <= 350
		  //reports->at(i).center_mass_y > 320 && 
		  //reports->at(i).center_mass_y < 540 &&
		  //reports->at(i).center_mass_x > 140 && 
		  //reports->at(i).center_mass_x < 340
		  ){
			printf("PASS");
			if(keeper == NULL){
				keeper = &reports->at(i);
			} else if (//particle is better than last
					   (absolute2(reports->at(i).center_mass_y_normalized) < absolute2(keeper->center_mass_y_normalized )) &&
					   (absolute2(reports->at(i).center_mass_x_normalized) < absolute2(keeper->center_mass_x_normalized ))){
				keeper = &reports->at(i);
			}
		} else {
			printf("FAIL ");
		}
	}
	if(keeper == NULL){
		if(thresh.counter < 3){
			FixThreshold(&thresh);
			printf("message1\n");
			goto ThresholdRedo;
			//rerun filtering with different specs.
		}
	}
	float halfViewX = 22.5;
	float halfViewY = 16.875;
	float x = keeper->center_mass_x_normalized * halfViewX;
	float y = keeper->center_mass_y_normalized * halfViewY;
	delete reports;
	delete image;
	AngleData a = {x,y};
	return a;
}

void Camera::FixThreshold(Camera::Thresh *thresh){
	thresh->threshold->plane1Low -= thresh->changeBy->plane1Low;
	thresh->threshold->plane2Low -= thresh->changeBy->plane2Low;
	thresh->threshold->plane3Low -= thresh->changeBy->plane3Low;
	thresh->threshold->plane1High += thresh->changeBy->plane1High;
	thresh->threshold->plane2High += thresh->changeBy->plane2High;
	thresh->threshold->plane3High += thresh->changeBy->plane3High;
	if(thresh->threshold->plane1Low < thresh->limits->plane1Low){
		thresh->threshold->plane1Low = thresh->limits->plane1Low;
	}
	if(thresh->threshold->plane2Low < thresh->limits->plane2Low){
		thresh->threshold->plane2Low = thresh->limits->plane2Low;
	}
	if(thresh->threshold->plane3Low < thresh->limits->plane3Low){
		thresh->threshold->plane3Low = thresh->limits->plane3Low;
	}
	if(thresh->threshold->plane1High < thresh->limits->plane1High){
		thresh->threshold->plane1High = thresh->limits->plane1High;
	}
	if(thresh->threshold->plane2High < thresh->limits->plane2High){
		thresh->threshold->plane2High = thresh->limits->plane2High;
	}
	if(thresh->threshold->plane3High < thresh->limits->plane3High){
		thresh->threshold->plane3High = thresh->limits->plane3High;
	}
	thresh->counter++;
	printf("Redoing the threshold. occurance no:%d",thresh->counter);
}

ParticleAnalysisReport* Camera::FindBottomRectangle(ParticleAnalysisReport *reports, unsigned int reportCount ) {//no & because its a class right?
    TEST_MSG("\nFindBottomRectangle(reports)\n");
    ParticleAnalysisReport *bottom = NULL;
    
    for (unsigned int i = 0; i < reportCount; i++ ) {
        ParticleAnalysisReport *report = &reports[i];
        double xNorm = report->center_mass_x_normalized;
        double yNorm = report->center_mass_y_normalized;
        int width = report->boundingRect.width;
        int height = report->boundingRect.height;
        double aspect = (double)width/height;
        printf(
            "\nparticle %d:  center = (%5g,%5g); size = (%3d,%3d); aspect = %g\n",
            report->particleIndex, xNorm, yNorm, width, height, aspect );
        // the rectangle must be wider than minimum fraction of image
        if ( width < WIDTH_FRACTION_MIN*report->imageWidth ) {
            TEST_MSG("             rectangle is too small\n");
            continue;
        }
        // the bounding rectangle aspect ratio must be within tolerance
        if ( aspect < ASPECT_MIN || ASPECT_MAX < aspect ) {
            TEST_MSG("             aspect ratio out of tolerance\n");
            continue;
        }
        // the center of the rectangle must be in the bottom of the image
        //SHOULD HAVE TO BE
        if ( yNorm >= 0 ) {
            TEST_MSG("             center of rectangle is in top of image\n");
            continue;
        }
        // the center of the rectangle is lower than any before
        if ( bottom == 0 || yNorm < bottom->center_mass_y_normalized ) {
            bottom = report;
        }
    }
    return bottom;
}

ParticleAnalysisReport* findBottomRectangle(vector<ParticleAnalysisReport> reports ) {//no & because its a class right?
    TEST_MSG("\nfindBottomRectangle(reports)\n");
    ParticleAnalysisReport *bottom = NULL;
    vector<ParticleAnalysisReport>::iterator it;
    
    for ( it = reports.begin(); it < reports.end(); it++ ) {
        ParticleAnalysisReport &report = *it;
        double xNorm = report.center_mass_x_normalized;
        double yNorm = report.center_mass_y_normalized;
        int width = report.boundingRect.width;
        int height = report.boundingRect.height;
        double aspect = (double)width/height;
        TEST_MSG(
            "\nparticle %d:  center = (%5g,%5g); size = (%3d,%3d); aspect = %g\n",
            report.particleIndex, xNorm, yNorm, width, height, aspect );
        // the rectangle must be wider than minimum fraction of image
        if ( width < WIDTH_FRACTION_MIN*report.imageWidth ) {
            TEST_MSG("             rectangle is too small\n");
            continue;
        }
        // the bounding rectangle aspect ratio must be within tolerance
        if ( aspect < ASPECT_MIN || ASPECT_MAX < aspect ) {
            TEST_MSG("             aspect ratio out of tolerance\n");
            continue;
        }
        // the center of the rectangle must be in the bottom of the image
        if ( yNorm >= 0 ) {
            TEST_MSG("             center of rectangle is in top of image\n");
            continue;
        }
        // the center of the rectangle is lower than any before
        if ( bottom == 0 || yNorm < bottom->center_mass_y_normalized ) {
            bottom = &report;
        }
    }
    return bottom;
}
