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
	float halfviewx = 22.5;
	float halfviewy = 16.875;
	AxisCamera &camera = AxisCamera::GetInstance("10.34.99.90");
	printf("Setting Camera Params\n");
	camera.WriteResolution(AxisCamera::kResolution_640x480);
	camera.WriteCompression(0);

	Thresh thresh = {new Threshold(245, 255, 90, 255, 90, 255), 10 , 5 , 0};
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
		thresh.threshold->plane1Low -= thresh.changeByDown;
		thresh.threshold->plane2Low -= thresh.changeByDown;
		thresh.threshold->plane3Low -= thresh.changeByDown;
		thresh.threshold->plane1High -= thresh.changeByUp;
		thresh.threshold->plane2High -= thresh.changeByUp;
		thresh.threshold->plane3High -= thresh.changeByUp;
		if(thresh.ranBy < 3){
			thresh.ranBy++;
			goto ThresholdRedo;
		}
		//rerun filtering with different specs.
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
		thresh.threshold->plane1Low -= thresh.changeByDown;
		thresh.threshold->plane2Low -= thresh.changeByDown;
		thresh.threshold->plane3Low -= thresh.changeByDown;
		thresh.threshold->plane1High -= thresh.changeByUp;
		thresh.threshold->plane2High -= thresh.changeByUp;
		thresh.threshold->plane3High -= thresh.changeByUp;
		if(thresh.ranBy < 3){
			thresh.ranBy++;
			goto ThresholdRedo;
		}
		//rerun filtering with different specs.
	}
	// get image.                                          
	// process it.                                                   <--\
	// filter rectangles w/ above specs.                                |
	// while we have no rectangles, change threshhold.(autonomus only);-/
	// pick the one close to the middle vertically.
	// pick the one closest to the middle horizontally.
	// GO!
	

	double turnanglex;
	double turnangley;
	//for (unsigned int i = 0; i < reports->size(); i++) {
	//printf("\nParticle: %d\n  Center_Mass_x: %d\n  Center_Mass_y: %d\n  \n", i, r->center_mass_x, r->center_mass_y);
	//printf("  Image Width: %d\n", keeper->imageWidth);
	//printf("  Image Height: %d\n", keeper->imageHeight);
	//printf("  Center Mass x: %d\n", keeper->center_mass_x);
	//printf("  Center Mass y: %d\n", keeper->center_mass_y);
	double normx = keeper->center_mass_x_normalized;		//percent of rect from center of image
	double normy = keeper->center_mass_y_normalized;
	//printf("  Center Mass (Norm) x: %f\n", normx);
	//printf("  Center Mass (Norm) y: %f\n", normy);
	//printf("  Particle Area: %f\n", keeper->particleArea);
	//printf("  Particle to Image Percent: %f\n", keeper->particleToImagePercent);
	//printf("  Particle Quality: %f\n", keeper->particleQuality);
	Rect rectangle = keeper->boundingRect;
	turnanglex = normx * halfviewx;
	turnangley = normy * halfviewy;
	
	delete reports;
	delete filteredImage;
	delete convexHullImage;
	delete bigObjectsImage;
	delete thresholdImage;
	delete image;
	
	AngleData angleData = {turnanglex, turnangley};
	
	return angleData;
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
