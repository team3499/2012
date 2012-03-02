#include "Camera.h"
#include "WPILib.h"
#include "Robotmap.h"
#include "Commands/CameraDefault.h"

Camera::Camera() : Subsystem("Camera"){
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

	Threshold threshold(245, 255, 90, 255, 90, 255);
	Threshold threshold2(150, 190, 230, 255, 230, 255);
	Threshold threshold3(255, 255, 0, 0, 0, 0);
	
	ParticleFilterCriteria2 criteria[] = {
		{IMAQ_MT_BOUNDING_RECT_WIDTH, 30, 400, false, false},
		{IMAQ_MT_BOUNDING_RECT_HEIGHT, 40, 400, false, false}
	};
										
	ColorImage *image;
	image = camera.GetImage()/*new RGBImage("/img/testImage2.bmp")*/;	// get the sample image from the cRIO flash
	image->Write("/img2.bmp");
	printf("Start Image Loaded\n");
	BinaryImage *thresholdImage = image->ThresholdRGB(threshold);	// get just the red target pixels
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
	
	float halfview = 22.5;
	//printf("\nParticles: %d\n", reports->size());
	
	double turnanglex;
	double turnangley;
	
	for (unsigned int i = 1; i < reports->size(); i++) {
		ParticleAnalysisReport *r = &(reports->at(i));
		printf("\nParticle: %d\n  Center_Mass_x: %d\n  Center_Mass_y: %d\n  \n", i, r->center_mass_x, r->center_mass_y);
		printf("  Image Width: %d\n", r->imageWidth);
		printf("  Image Height: %d\n", r->imageHeight);
		printf("  Center Mass x: %d\n", r->center_mass_x);
		printf("  Center Mass y: %d\n", r->center_mass_y);
		double normx = r->center_mass_x_normalized;		//percent of rect from center of image
		double normy = r->center_mass_y_normalized;
		printf("  Center Mass (Norm) x: %f\n", normx);
		printf("  Center Mass (Norm) y: %f\n", normy);
		printf("  Particle Area: %f\n", r->particleArea);
		printf("  Particle to Image Percent: %f\n", r->particleToImagePercent);
		printf("  Particle Quality: %f\n", r->particleQuality);
		Rect rectangle = r->boundingRect;
		printf("\n  Rectangle:\n");
		printf("    Rect Top-Left Coord: (%d,%d)\n", rectangle.left, rectangle.top);
		printf("    Rect Height: %d\n", rectangle.height);
		printf("    Rect Width: %d\n", rectangle.width);
		turnanglex = normx * halfview;
		printf("\n  Angle to Turn: %f\n", turnanglex); //negative value means left, positive = right
	}
	printf("\n");
	
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

