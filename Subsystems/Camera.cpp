#include "Camera.h"
#include "WPILib.h"
#include "Robotmap.h"

float absolute2(float x) {
  if (x < 0) {
    return -x;
  } else
    return x;
}

// predicate used to detect small particles
static bool isSmallParticle(ParticleAnalysisReport particle) {
  return (particle.boundingRect.height < 80 || particle.boundingRect.width < 90);
}

// predicate used to detect huge particles
static bool isHugeParticle(ParticleAnalysisReport particle) {
  return (particle.boundingRect.height > 300 || particle.boundingRect.width > 350);
}

// predicate used to detect height>width particles
static bool isTallParticle(ParticleAnalysisReport particle) {
  return (particle.boundingRect.height > particle.boundingRect.width);
}

// predicate used to detect height>width particles
static bool isNotWideRectParticle(ParticleAnalysisReport particle) {
  return ((particle.boundingRect.height < (particle.boundingRect.width / 2.4)) ||
		  (particle.boundingRect.height > (particle.boundingRect.width / 1.4)));//THIS WAS 1.7
}

Camera::Camera() :
  Subsystem("Camera")
{
  // Set adaptive thresholds.
  thresholds[0] = new Threshold(190, 255, 70, 255, 70, 255);
  thresholds[1] = new Threshold(180, 255, 65, 255, 65, 255);
  thresholds[2] = new Threshold(170, 255, 60, 255, 60, 255);
  thresholds[3] = new Threshold(160, 255, 55, 255, 55, 255);
  thresholds[4] = NULL;   // MUST have a NULL at the end! (so we dont run a marathon through the memory)
  lastGoodTarget = NULL;  // to test if it is there or not
  status = false;
/*AxisCamera &camera = AxisCamera::GetInstance(CAMERA_IP_ADDR);
  camera.WriteResolution(AxisCamera::kResolution_640x480);
  camera.WriteCompression(0);
  if(camera.StatusIsFatal()){
	  printf("No good. No camera.\n");
	  camera.DeleteInstance();
	  status = false;
	  camera.
	  camera.~AxisCamera();
  } else {
	  printf("Got the camera\n");
    ColorImage *image = camera.GetImage();
    delete image;
    status = true;
  }
  */
}

// Get the preferred target to shoot at.  Caller is responsible for freeing
// the returned Target object.
Target * Camera::GetTarget() {
  if (status == false){
	  SetLastGoodTarget(NULL);
	  return NULL;
  }
  // Capture image
  ColorImage *image = CaptureImage();

  // Produce list of particles that could be targets
  vector<ParticleAnalysisReport> *particles = GetPotentialParticles(image, thresholds);
  delete image;

  if (particles == NULL) {  // Total Failure!  Bail out returning 0, 0 for angle data
    if (IS_DEBUG_MODE) { printf("#### Total Failure!  No target acquired! Did not set lastGoodTarget to anything new.\n"); }
    SetLastGoodTarget(NULL);
    return NULL;
  }

  // Select a target to shoot at
  Target *target = SelectPreferredTarget(particles);
  delete particles;
  
  SetLastGoodTarget(target);
  SmartDashboard::Log(target->GetHorizontalAngle(),"Target Offset");
  printf("Target Offset:%f\n",target->GetHorizontalAngle());
  return target;
}

//
// Capture an image from the camera.  Caller is responsible for
// freeing the ColorImage object returned.
//
ColorImage * Camera::CaptureImage() {
  AxisCamera &camera = AxisCamera::GetInstance(CAMERA_IP_ADDR);
  camera.WriteResolution(AxisCamera::kResolution_640x480);
  camera.WriteCompression(0);

  ColorImage *image = camera.GetImage();
  if (IS_DEBUG_MODE) {
    printf("#### Captured camera image to /img/picture.png");
    image->Write("/img/picture.png");
  }

  return image;
}

//
// Given a CameraImage and a list of Thresholds to apply, try to produce a workable
// list of particles as potential targets.  If no workable particles are found,
// return NULL.
//
// Caller is required to free the vector returned.
//
vector<ParticleAnalysisReport> * Camera::GetPotentialParticles(ColorImage *image, Threshold *thresholds[]) {
  vector<ParticleAnalysisReport> *particles = NULL;
  int thresholdIndex = 0;

  // Loop over thresholds applying each in turn to the camera image.  If successful,
  // will return a non-NULL pointer for the particle list.
  while (thresholds[thresholdIndex] != NULL) {
    if (IS_DEBUG_MODE) { printf("#### Evaluating "); }
    if (IS_DEBUG_MODE) { OutputThreshold(thresholds[thresholdIndex]); }

    // Process captured image to produce an ordered list of particles
    particles = ProcessImageForReport(image, thresholds[thresholdIndex], thresholdIndex++);
    if (IS_DEBUG_MODE) { printf("#### %d Potential Particles\n", particles->size()); }
    if (IS_DEBUG_MODE) { OutputParticles(particles); }

    // Reject particles that are too small, too large, or taller than they are wide
    //particles->erase(std::remove_if(particles->begin(), particles->end(), isSmallParticle), particles->end());
    //particles->erase(std::remove_if(particles->begin(), particles->end(), isHugeParticle), particles->end());
    //particles->erase(std::remove_if(particles->begin(), particles->end(), isTallParticle), particles->end());
    particles->erase(std::remove_if(particles->begin(), particles->end(), isNotWideRectParticle), particles->end());
    if (IS_DEBUG_MODE) { printf("#### %d Filtered Particles\n", particles->size()); }
    if (IS_DEBUG_MODE) { OutputParticles(particles); }

    // Try again with the next threshold in the list
    // if no "good" particles left in the list
    if (particles->size() == 0) {
      delete particles;
      particles = NULL;
      continue;
    } else {
      break;
    }
  }

  return particles;  // Will return NULL if there is no good particles.
}

// Given a list of particles, return the preferred target to shoot at.  Caller
// is responsible for freeing the returned Target object.
Target * Camera::SelectPreferredTarget(vector<ParticleAnalysisReport> *particles) {

  // Select the largest particle
  ParticleAnalysisReport largestParticle = particles->at(0);
  ParticleAnalysisReport lowestParticle  = particles->at(0);
  if (IS_DEBUG_MODE) {
    printf("#### Initial Largest ");
    OutputParticle(&largestParticle);
    printf("#### Initial Lowest ");
    OutputParticle(&lowestParticle);
  }
  for (vector<ParticleAnalysisReport>::iterator iter = particles->begin(); iter != particles->end(); ++iter ) {
    if (iter->particleArea > largestParticle.particleArea) {
      largestParticle = *iter;
      if (IS_DEBUG_MODE) {
        printf("#### New Largest ");
        OutputParticle(&largestParticle);
      }
    }
    if (iter->center_mass_y > lowestParticle.center_mass_y) {
      lowestParticle = *iter;
      if (IS_DEBUG_MODE) {
        printf("#### New Lowest ");
        OutputParticle(&lowestParticle);
      }
    }
  }

  // We're going to shoot at the largest target.  Get the horizontal angle
  // and assume it's a middle height target.
  float hAngle = largestParticle.center_mass_x_normalized * 22.5;
  Target::ID targetID = Target::Middle;

  // If lowest and largest particle are the same, then we are probably
  // right in front of the bottom target.  Adjust the target ID.
  if (lowestParticle.particleIndex == largestParticle.particleIndex) { targetID = Target::Bottom; }

  Target *target = new Target(targetID, hAngle);
  if (true) {
    printf("#### Selected ");
    OutputParticle(&largestParticle);
    printf("#### Selected ");
    OutputTarget(target);
  }

  return target;
}

/* *\ 
 * Get the particle analysis report with a threshold.
 * args: which threshold to USE 0-3 NOT 4
\* */
vector<ParticleAnalysisReport> *Camera::ProcessImageForReport(ColorImage *image, Threshold *threshold, int index) {

  BinaryImage *thresholdImage = image->ThresholdRGB(*threshold); // get just the red target pixels
  BinaryImage *bigObjectsImage = thresholdImage->RemoveSmallObjects(false, 4); // remove small objects (noise)
  BinaryImage *convexHullImage = bigObjectsImage->ConvexHull(false); // fill in partial and full rectangles
  ParticleFilterCriteria2 criteria[] = { { IMAQ_MT_BOUNDING_RECT_WIDTH, 30, 400, false, false },
                                         { IMAQ_MT_BOUNDING_RECT_HEIGHT, 40, 400, false, false } };
  BinaryImage *filteredImage = convexHullImage->ParticleFilter(criteria, 2); // find the rectangles
  vector<ParticleAnalysisReport> *reports = filteredImage->GetOrderedParticleAnalysisReports();

  if(IS_DEBUG_MODE){
    char filenames[4][16];
    sprintf(filenames[0], "/img/%dimg1.png", index);
    sprintf(filenames[1], "/img/%dimg2.png", index);
    sprintf(filenames[2], "/img/%dimg3.png", index);
    sprintf(filenames[3], "/img/%dimg4.png", index);
    printf("#### Threshold image written to %s\n", filenames[0]);
    thresholdImage->Write(filenames[0]);
    printf("#### Big objects image written to %s\n", filenames[1]);
    bigObjectsImage->Write(filenames[1]);
    printf("#### Convex hull image written to %s\n", filenames[2]);
    convexHullImage->Write(filenames[2]);
    printf("#### Filtered image written to %s\n", filenames[3]);
    filteredImage->Write(filenames[3]);
  }

  delete convexHullImage;
  delete bigObjectsImage;
  delete thresholdImage;
  delete filteredImage;

  return reports;
}



void Camera::OutputThreshold(Threshold *threshold) {
  printf("Threshold: %03d/%03d %03d/%03d %03d/%03d\n", threshold->plane1Low, threshold->plane1High,
         threshold->plane2Low, threshold->plane2High, threshold->plane3Low, threshold->plane3High);
}

void Camera::OutputParticle(ParticleAnalysisReport *particle) {
  printf("Particle: #%d W:%d H:%d (Aspect Ratio:%0.1f) Area:%0.1f Center:%dx%d %0.1f%%\n",
		 particle->particleIndex,
         particle->boundingRect.width,
         particle->boundingRect.height,
         (float)((float)particle->boundingRect.width/(float)particle->boundingRect.height),
         particle->particleArea,
         particle->center_mass_x,
         particle->center_mass_y,
         particle->particleToImagePercent);
}

void Camera::OutputParticles(vector<ParticleAnalysisReport> *particles) {
  for (vector<ParticleAnalysisReport>::iterator iter = particles->begin(); iter != particles->end() ; ++iter) {
    OutputParticle(&(*iter));
  }
}

void Camera::OutputTarget(Target *target) {
  printf("Target: %s\n", target->AsString());
}

/***************************\
*   Last-Good-Target stuff  *
\***************************/

void Camera::SetLastGoodTarget(Target *target){
  lastGoodTarget = target;
  if(IS_DEBUG_MODE){
	  printf("Set lastGoodTarget\n");
  }
}

Target * Camera::GetLastGoodTarget(){
  if(status == NULL) return NULL;
  return lastGoodTarget; // if not lastGoodTarget is not used, it will return NULL
}
