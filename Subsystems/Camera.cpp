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

	Thresh thresh = {new Threshold(245, 255, 90,  255, 90,  255),//starting
			         new Threshold(10,  5,   10,  5,   10,  5),//change by this much
			         new Threshold(128, 255, 128, 255, 128, 255),//not more/less than this
			         0};
	Threshold threshold2(130, 180, 170, 225, 240, 255);
	//Threshold threshold3(255, 255, 0, 0, 0, 0);
	
	ThresholdRedo:
	
	ParticleFilterCriteria2 criteria[] = {
		{IMAQ_MT_BOUNDING_RECT_WIDTH, 30, 400, false, false},
		{IMAQ_MT_BOUNDING_RECT_HEIGHT, 40, 400, false, false}
	};
										
	ColorImage *image;
	image = camera.GetImage()/*new RGBImage("/img/testImage2.bmp")*/;	// get the sample image from the cRIO flash
	image->Write("/img2.bmp");
	printf("Start Image Loaded\n");
	BinaryImage *thresholdImage = image->ThresholdRGB(threshold2);	// get just the red target pixels
	thresholdImage -> Write("/timg2.png");
	printf("Threshold Written\n");
	BinaryImage *bigObjectsImage = thresholdImage->RemoveSmallObjects(false, 2);  // remove small objects (noise)
	bigObjectsImage -> Write("/timg3.png");
	printf("Big Objects Written\n");
	BinaryImage *convexHullImage = bigObjectsImage->ConvexHull(false);  // fill in partial and full rectangles
	convexHullImage -> Write("/timg4.png");
	printf("Convex Hull Written\n");
	BinaryImage *filteredImage = convexHullImage->ParticleFilter(criteria, 2);  // find the rectangles
	filteredImage -> Write("/img/timg5.png");
	printf("Filtered Image Written\n");
	vector<ParticleAnalysisReport> *reports = filteredImage->GetOrderedParticleAnalysisReports();
	
	particleCount = reports->size();
	
	//printf("\nParticles: %d\n", reports->size());
	
	//if r->area > 3000 && r->height > 80 && r->width > 90 {GOOD RECTANGLE!}
	if(!reports->size()){
		if(thresh.counter < 3){
			thresh.threshold->plane1Low -= thresh.changeBy->plane1Low;
			thresh.threshold->plane2Low -= thresh.changeBy->plane2Low;
			thresh.threshold->plane3Low -= thresh.changeBy->plane3Low;
			thresh.threshold->plane1High += thresh.changeBy->plane1High;
			thresh.threshold->plane2High += thresh.changeBy->plane2High;
			thresh.threshold->plane3High += thresh.changeBy->plane3High;
			if(thresh.threshold->plane1Low < thresh.limits->plane1Low){
				thresh.threshold->plane1Low = thresh.limits->plane1Low;
			}
			if(thresh.threshold->plane2Low < thresh.limits->plane2Low){
				thresh.threshold->plane2Low = thresh.limits->plane2Low;
			}
			if(thresh.threshold->plane3Low < thresh.limits->plane3Low){
				thresh.threshold->plane3Low = thresh.limits->plane3Low;
			}
			if(thresh.threshold->plane1High < thresh.limits->plane1High){
				thresh.threshold->plane1High = thresh.limits->plane1High;
			}
			if(thresh.threshold->plane2High < thresh.limits->plane2High){
				thresh.threshold->plane2High = thresh.limits->plane2High;
			}
			if(thresh.threshold->plane3High < thresh.limits->plane3High){
				thresh.threshold->plane3High = thresh.limits->plane3High;
			}
			thresh.counter++;
			goto ThresholdRedo;
			//rerun filtering with different specs.
		}
	}
	
	ParticleAnalysisReport *keeper = NULL;
	for (unsigned int i = 0; i < reports->size(); i++){
		if(reports->at(i).boundingRect.height >= 80 && 
		  reports->at(i).boundingRect.width >= 90 && 
		  reports->at(i).boundingRect.height <= 300 && 
		  reports->at(i).boundingRect.width >= 350
		  //reports->at(i).center_mass_y > 320 && 
		  //reports->at(i).center_mass_y < 540 &&
		  //reports->at(i).center_mass_x > 140 && 
		  //reports->at(i).center_mass_x < 340
		  ){
			if(keeper == NULL){
				keeper = &reports->at(i);
			} else if (//particle is better than last
					   (absolute2(reports->at(i).center_mass_y_normalized) < absolute2(keeper->center_mass_y_normalized )) &&
					   (absolute2(reports->at(i).center_mass_x_normalized) < absolute2(keeper->center_mass_x_normalized ))){
				keeper = &reports->at(i);
			}
		}
	}
	if(keeper == NULL){
		if(thresh.counter < 3){
		 thresh.threshold->plane1Low -= thresh.changeBy->plane1Low;
		 thresh.threshold->plane2Low -= thresh.changeBy->plane2Low;
		 thresh.threshold->plane3Low -= thresh.changeBy->plane3Low;
		 thresh.threshold->plane1High += thresh.changeBy->plane1High;
		 thresh.threshold->plane2High += thresh.changeBy->plane2High;
		 thresh.threshold->plane3High += thresh.changeBy->plane3High;
			if(thresh.threshold->plane1Low < thresh.limits->plane1Low){
				thresh.threshold->plane1Low = thresh.limits->plane1Low;
			}
			if(thresh.threshold->plane2Low < thresh.limits->plane2Low){
				thresh.threshold->plane2Low = thresh.limits->plane2Low;
			}
			if(thresh.threshold->plane3Low < thresh.limits->plane3Low){
				thresh.threshold->plane3Low = thresh.limits->plane3Low;
			}
			if(thresh.threshold->plane1High < thresh.limits->plane1High){
				thresh.threshold->plane1High = thresh.limits->plane1High;
			}
			if(thresh.threshold->plane2High < thresh.limits->plane2High){
				thresh.threshold->plane2High = thresh.limits->plane2High;
			}
			if(thresh.threshold->plane3High < thresh.limits->plane3High){
				thresh.threshold->plane3High = thresh.limits->plane3High;
			}
			thresh.counter++;
			goto ThresholdRedo;
			//rerun filtering with different specs.
		}
	}
	float x = keeper->center_mass_x_normalized * halfViewX;
	float y = keeper->center_mass_y_normalized * halfViewY;
	delete reports;
	delete filteredImage;
	delete convexHullImage;
	delete bigObjectsImage;
	delete thresholdImage;
	delete image;
	AngleData a = {x,y};
	return a;
}
