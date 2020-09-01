struct Quaternion {
  double w, x, y, z;
};

Quaternion ToQuaternion(double yaw, double pitch, double roll){
  double cy = cos(yaw*0.5);
  double sy = sin(yaw*0.5);
  double cp = cos(pitch*0.5);
  double sp = sin(pitch*0.5);
  double cr = cos(roll*0.5);
  double sr = sin(roll*0.5);

  Quaternion q;
  q.w = cr * cp * cy + sr * sp * sy;
  q.x = sr * cp * cy - cr * sp * sy;
  q.y = cr * sp * cy + sr * cp * sy;
  q.z = cr * cp * sy - sr * sp * cy;

  return q;
}

Quaternion K_Product(Quaternion q_m, Quaternion q_r){
  //This function will perform a Kronecker Product multiplication
  //on two quaternions: q_m = the measured state
  //                    q_r = the desired state
  //And output the error correction required to go from q_m to q_r:
  //                    q_err = the error quaternion
  
  Quaternion q_err;
  q_err.w = q_m.w*q_r.w - q_m.x*q_r.x - q_m.y*q_r.y - q_m.z*q_r.z;
  q_err.x = q_m.w*q_r.x - q_m.x*q_r.w - q_m.y*q_r.z - q_m.z*q_r.y;
  q_err.y = q_m.w*q_r.y - q_m.x*q_r.z - q_m.y*q_r.w - q_m.z*q_r.x;
  q_err.z = q_m.w*q_r.z - q_m.x*q_r.y - q_m.y*q_r.x - q_m.z*q_r.w;

  return q_err;  
}
