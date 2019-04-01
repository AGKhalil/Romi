
void goStraightSpiral() {
  outputPIDdistance = distancePID.Compute(totalDistance, targetDistance, false);
  outputPIDangle = anglePID.Compute(angle, targetAngle, false);

  double leftOut = outputPIDdistance - outputPIDangle;
  double rightOut = outputPIDdistance + outputPIDangle;

  motors.setLeftSpeed(leftOut);
  motors.setRightSpeed(rightOut);

  //Check if object in the way
  distance = readDistance();
  
  if(distance <= 6 || abs(totalDistance - targetDistance) < 100) {
    int randomSide = (int)random(-1,1);
    targetAngle = angle + (randomSide * 90);
    targetDistance = totalDistance + 6000 ;
    state = 1;
    logarithmicCount = 0;
  }

  
}

void goSpiral() {
  outputPIDdistance = distancePID.Compute(totalDistance, targetDistance, false);
  outputPIDangle = anglePID.Compute(angle, targetAngle, false);
  logarithmicCount += 0.001;
  double spiralFactor = 2.5*atan(log(sqrt(logarithmicCount+1))) / PI;

  double leftOut = spiralFactor * outputPIDdistance;
  double rightOut = outputPIDdistance;

  motors.setLeftSpeed(leftOut);
  motors.setRightSpeed(rightOut);

  //Check if object in the way
  distance = readDistance();
  
  if(distance <= 6 || abs(totalDistance - targetDistance) < 100) {
    int randomSide = (int)random(-1,1);
    targetAngle = angle + (randomSide * 90);
    state = 2;
  }

  
}

void turnRandomSpiral() {
  outputPIDangle = anglePID.Compute(angle, targetAngle, false);
  
  double leftOut = -outputPIDangle;
  double rightOut = outputPIDangle;

  if(leftOut >= 2 && leftOut <= 26) {
    leftOut = 23;
  }
  if(leftOut >= -26 && leftOut <= -2) {
    leftOut = -23;
  }

  if(rightOut >= 2 && rightOut <= 26) {
    rightOut = 23;
  }
  if(rightOut >= -26 && rightOut <= -2) {
    rightOut = -23;
  }

  motors.setLeftSpeed(leftOut);
  motors.setRightSpeed(rightOut);

  if(((angle-targetAngle) > -0.5) && ((angle-targetAngle) < 0.5) && (outputPIDangle > -3) && (outputPIDangle < 3)) {
    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);

    targetDistance = totalDistance + 1000 ;

    state = 3;

  }

}

void doNothing() {
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
}

