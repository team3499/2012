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
	float halfViewX = 22.5;
	float halfViewY = 16.875;
	AxisCamera &camera = AxisCamera::GetInstance("10.34.99.90");
	printf("Setting Camera Params\n");
	camera.WriteResolution(AxisCamera::kResolution_640x480);
	camera.WriteCompression(0);
	
	Thresh thresh = {new Threshold(190, 255, 70,  255, 70,  255),//starting
			         new Threshold(10,  5,   10,  5,   10,  5),//change by this much
			         new Threshold(180, 255, 60,  255, 60,  255),//not more/less than this
			         0};
	
	Threshold threshold2(130, 180, 170, 225, 240, 255);
	//Threshold threshold3(255, 255, 0, 0, 0, 0);
	ColorImage *image;
	image = camera.GetImage();
	image->Write("/img/picture.png");
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
	BinaryImage *bigObjectsImage = thresholdImage->RemoveSmallObjects(false, 4);  // remove small objects (noise)
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
		if(thresh.counter < 5){
			FixThreshold(&thresh);
			printf("message0");
			goto ThresholdRedo;
			//rerun filtering with different specs.
		}
	}
	
	ParticleAnalysisReport *keeper = NULL;
	bool good[reports->size()];
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
			if (//particle is better than last
					   (absolute2(reports->at(i).center_mass_y_normalized) < absolute2(keeper->center_mass_y_normalized )) &&
					   (absolute2(reports->at(i).center_mass_x_normalized) < absolute2(keeper->center_mass_x_normalized ))){
				keeper = &reports->at(i);
			}
			good[i] = true;
		} else {
			good[i] = false;
			printf("FAIL ");
		}
		
	}
	unsigned int count = 0;
	for (unsigned int i = 0; i < reports->size(); i++){
		count += good[i];
	}
	if(!count){
		if(thresh.counter < 5){
			FixThreshold(&thresh);
			printf("message1\n");
			goto ThresholdRedo;
			//rerun filtering with different specs.
		} else {
			AngleData a;
			return a;
		}
	}
	ParticleAnalysisReport *keeps[count];
	count = 0;
	for (unsigned int i = 0; i < reports->size(); i++){
		if(good[i]){
			keeps[count] = &reports->at(i);
			count++;
		}
	}
	TEST_MSG("\nFindBottomRectangle(reports)\n");
	keeper = NULL;
	for (unsigned int i = 0; i < count; i++ ) {
	    ParticleAnalysisReport *report = keeps[i];
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
	  //  if ( yNorm >= 0 ) {
	  //      TEST_MSG("             center of rectangle is in top of image\n");
	  //      continue;
	  //  }
	    // the center of the rectangle is lower than any before
	    if ( keeper == NULL || yNorm > keeper->center_mass_y_normalized ) {
	        keeper = report;
	    }
	}
	printf("\nCamera Coords:\n\t\tParticle:Bottom\n\t\tx:%f\n\t\ty:%f\n",
			halfViewX * keeper->center_mass_x_normalized,
			halfViewY * keeper->center_mass_y_normalized);
	ParticleAnalysisReport *bottom = keeper;
	ParticleAnalysisReport *middle1 = 0;
	ParticleAnalysisReport *middle2 = 0;
	double bottomWidth  = 2.0*bottom->boundingRect.width/bottom->imageHeight;
	double bottomHeight = 2.0*bottom->boundingRect.height/bottom->imageWidth;
	TEST_MSG("bottom: width = %3g; height = %3g\n",bottomWidth,bottomHeight);
	double xLeft  = bottom->center_mass_x_normalized-bottomWidth*0.5;
	double xRight = bottom->center_mass_x_normalized+bottomWidth*0.5;
	double yMin   = bottom->center_mass_y_normalized+bottomHeight*1.5;
	for (unsigned int i = 0; i < count; i++ ) {
	    ParticleAnalysisReport &report = *keeps[i];
	    if ( report.particleIndex == bottom->particleIndex ) {
	        continue;
	    }
	    double y = report.center_mass_y_normalized;
	    double x = report.center_mass_x_normalized;
	    // the center of the rectangle must be far enough above the bottom one
	    if ( y > yMin ) {
	        TEST_MSG("             center of rectangle is too low\n");
	        continue;
	    }
	    // the rectangle must not be centered over the bottom one
	    if ( xLeft < x && x < xRight ) {
	        TEST_MSG("             center of rectangle is too centered\n");
	        continue;
	    }
	    if ( middle1 == 0 ) {
	        middle1 = &report;
	    } else if ( middle2 == 0 ) {
	        middle2 = &report;
	    }
	}
	if ( middle1 ) {
		printf("\nCamera Coords:\n\t\tParticle:Middle1\n\t\tx:%f\n\t\ty:%f\n",
				halfViewX * middle1->center_mass_x_normalized,
				halfViewY * middle1->center_mass_y_normalized);
	    if ( middle2 ) {
			printf("\nCamera Coords:\n\t\tParticle:Middle2\n\t\tx:%f\n\t\ty:%f\n",
					halfViewX * middle2->center_mass_x_normalized,
					halfViewY * middle2->center_mass_y_normalized);
	        // pick the larger of the two because it's closer
	        if ( middle2->boundingRect.width > middle1->boundingRect.width ) {
	            middle1 = middle2;
	        }
	    }
	}

	printf("\nCamera Coords:\n\t\tParticle:The Chosen One\n\t\tx:%f\n\t\ty:%f\n",
			halfViewX * middle1->center_mass_x_normalized,
			halfViewY * middle1->center_mass_y_normalized);
	float x = middle1->center_mass_x_normalized * halfViewX;
	float y = middle1->center_mass_y_normalized * halfViewY;
	FILE *fp2 = CommandBase::GetOIInstance()->fp;
	fprintf(fp2,"X:%f\n Y:%f\n",x,y);
	printf("PARTICLE: X:%f, Y:%f                        ",x,y);
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

ParticleAnalysisReport* Camera::FindBottomRectangle(ParticleAnalysisReport *reports[], unsigned int reportCount ) {//no & because its a class right?
    TEST_MSG("\nFindBottomRectangle(reports)\n");
    ParticleAnalysisReport *bottom = NULL;
    
    for (unsigned int i = 0; i < reportCount; i++ ) {
        ParticleAnalysisReport *report = reports[i];
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


ParticleAnalysisReport* findMiddleRectangle( 
        vector<ParticleAnalysisReport>& reports, int bottomIndex ) {
    TEST_MSG("\nfindMiddleRectangle(reports,%d)\n",bottomIndex);
    ParticleAnalysisReport& bottom = reports.at(bottomIndex);
    ParticleAnalysisReport* middle1 = 0;
    ParticleAnalysisReport* middle2 = 0;
    vector<ParticleAnalysisReport>::iterator it;
    double bottomWidth  = 2.0*bottom.boundingRect.width/bottom.imageHeight;
    double bottomHeight = 2.0*bottom.boundingRect.height/bottom.imageHeight;
    TEST_MSG("bottom: width = %3g; height = %3g\n",bottomWidth,bottomHeight);
    double xLeft  = bottom.center_mass_x_normalized-bottomWidth*0.5;
    double xRight = bottom.center_mass_x_normalized+bottomWidth*0.5;
    double yMin   = bottom.center_mass_y_normalized+bottomHeight*1.5;
    for ( it = reports.begin(); it < reports.end(); it++ ) {
        ParticleAnalysisReport& report = *it;
        if ( report.particleIndex == bottomIndex ) {
            continue;
        }
        //if ( !acceptableRectangle(report) ) {
        //    continue;
       // }
        double y = report.center_mass_y_normalized;
        double x = report.center_mass_x_normalized;
        // the center of the rectangle must be far enough above the bottom one
        if ( y < yMin ) {
            TEST_MSG("             center of rectangle is too low\n");
            continue;
        }
        // the rectangle must not be centered over the bottom one
        if ( xLeft < x && x < xRight ) {
            TEST_MSG("             center of rectangle is too centered\n");
            continue;
        }
        if ( middle1 == 0 ) {
            middle1 = &report;
        } else if ( middle2 == 0 ) {
            middle2 = &report;
        }
    }
    if ( middle1 ) {
        if ( middle2 ) {
            // pick the larger of the two because it's closer
            if ( middle2->boundingRect.width > middle1->boundingRect.width ) {
                middle1 = middle2;
            }
        }
    }
    return middle1;
}
