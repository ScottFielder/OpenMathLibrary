
#include <iostream>
#include <fstream>
#include <algorithm> 
#include "DebugUtlities.h"
#include "MathLib.h"
#include "MathLibEx.h"

#include "Main.h"

using namespace MATH;
using namespace MATHEX;
using namespace glm;
using namespace std;

int main(int argc, char* argv[]) {
	inverseTestMat4();
	lookAtTest();
	determinantTest();
	hashTest();
	rotationIsOrthogonal();
	multiplyMatrixTest();

	dqTranslateAlongLineTest();       // GREEN for GOOD!
	lookAtTest();                   // GREEN for GOOD!
	dqGetRotationTranslationTest();   // GREEN for GOOD!
	dualQuatMatrixTest();             // GREEN for GOOD!
	dqConstructorTest();              // GREEN for GOOD!
	dualQuatTest();                   // GREEN for GOOD!
	dualQuatSlerpTest();              // GREEN for GOOD!
	projectTest();					  // GREEN for GOOD!
	quadAreaTest();				      // GREEN for GOOD!
	closestPointOnQuadTest();         // GREEN for GOOD!
	pointInsideQuadTest();			  // GREEN for GOOD!
	triangleTest();					  // GREEN for GOOD!
	planeTest();					  // GREEN for GOOD!
	raySphereTest();			      // GREEN for GOOD!
	rotateTest();				      // GREEN for GOOD!
	translateTest();				  // GREEN for GOOD!
	quadraticTest();
	rayTest();
	//flectorTest();
	//intersectionTest();
	//dualTest();
	//meetTest();
	//joinTest();
	//rotateTest();
	//gradeTest();
	//normalizeLineTest();
	//rayPlaneTest();
	//dotTest();
	//point2dTest();				  // Just simple operator tests
	//sphereTest();					  // Just a timing test
}


void slerpTest() {
	Euler e1(90.0f, 0.0f, 0.0f);
	Quaternion q1 = QMath::toQuaternion(e1);
	q1.print("Start");

	Euler e2(0.0f, 90.0f, 0.0f);
	Quaternion q2 = QMath::toQuaternion(e2);
	q2.print("End");

	for (float t = 0.0f; t < 1.1f; t+=0.1f) {
		Quaternion q = QMath::slerp(q1, q2, t);
		q.print("slerping");
	}

}

void determinantTest(){
	const string name = " DeterminantTest";
	/// These vectors should return a value of 30 - it does.
	/// Swap any two and the sign should change - it does
	Matrix4 m4;
	m4.setColumn(Matrix4::Colunm::zero,Vec4(1.0f, 0.0f, 2.0f, -1.0f));
	m4.setColumn(Matrix4::Colunm::one, Vec4(3.0f, 0.0f, 0.0f, 5.0f));
	m4.setColumn(Matrix4::Colunm::two, Vec4(2.0f, 1.0f, 4.0f, -3.0f));
	m4.setColumn(Matrix4::Colunm::three,Vec4(1.0f, 0.0f, 5.0f, 0.0f));
	bool test0 = compare(MMath::determinate(m4), 30.0f, 1.0e-6f);


	m4.setColumn(Matrix4::Colunm::zero, Vec4(3.0f, 0.0f, 0.0f, 5.0f));/// Swap this 
	m4.setColumn(Matrix4::Colunm::one, Vec4(1.0f, 0.0f, 2.0f, -1.0f));/// with this
	m4.setColumn(Matrix4::Colunm::two, Vec4(2.0f, 1.0f, 4.0f, -3.0f));
	m4.setColumn(Matrix4::Colunm::three, Vec4(1.0f, 0.0f, 5.0f, 0.0f));
	bool test1 = compare(MMath::determinate(m4), -30.0f, 1.0e-6f);

	/// deternimant of the identity matrix = 1.0 
	Matrix3 m2;
	bool test2 = MMath::determinate(m2);
	if( test0 && test1 && test2){
		printPassedOrFailed(true, name);
	}
	else {
		printPassedOrFailed(false, name);
	}
}

void hashTest(){
	const string name = " hashTest";
	Vec3 v1(1.1f, 1.0f, 1.0f);
	Vec3 v2(1.1f, 1.0f, 1.0f);

	/// operator == is overloaded to do a binary comparison of two Vec3s
	bool test0 = (v1 == v2);

	vec3 glmV1(1.1f, 1.0f, 1.0f);
	vec3 glmV2(1.1f, 1.0f, 1.0f);
	
	bool test1 = (glmV1 == glmV2);

	hash<Vec3> hasher;
	size_t myHash = hasher(v1);
	 
	hash<vec3> glmHasher;
	size_t glmHash = glmHasher(glmV1);
	bool test3 = (myHash == glmHash);
	

	/// Test if I can do a hash test between vertices using an unordered_map count() function  
	std::unordered_map<Vec3, uint32_t> uniqueVerts;
	uint32_t count = 0;
	if (uniqueVerts.count(v1) == 0) {
		uniqueVerts[v1] = count;
		++count;
	}

	if (uniqueVerts.count(v2) == 0) {
		uniqueVerts[v2] = count;
		++count;
	}


	/// Compare it with glm
	std::unordered_map<vec3, uint32_t> glmUniqueVerts;
	uint32_t glmCount = 0;
	if(glmUniqueVerts.count(glmV1) == 0){
		glmUniqueVerts[glmV1] = glmCount;
		++glmCount;
	}

	if (glmUniqueVerts.count(glmV2) == 0) {
		glmUniqueVerts[glmV2] = glmCount;
		++glmCount;
	}
	
	bool test2 = (count == glmCount);

	if (test0 && test1 && test2 ) {
		printPassedOrFailed(true, name);
	}
	else {
		printPassedOrFailed(false, name);
	}
}

void quaternionTest() {
	//Quaternion qLookat = QMath::lookAt(Vec3(1.0f, 0.0f, 1.0f),Vec3(0.0f, 1.0f, 0.0));
	//qLookat.print();
	//
	//glm::quat glmlookat = glm::quatLookAt(normalize(vec3(1.0f, 0.0f, 1.0)), vec3(0.0f, 1.0f, 0.0));
	//glmPrintQ(glmlookat,"glm lookat");


	//Matrix3 rm = Matrix3 (MMath::rotate(-270.0f, Vec3(1.0f, 0.0f, 0.0f)));
	//rm.print("My rotation matrix");
	//Quaternion qm = QMath::toQuaternion(rm);
	//qm.print("Quaternion rotate");
	//Matrix4 meMat = MMath::toMatrix4(qm);
	//meMat.print("My matrix from Q");

	//mat3 glmrot = mat3(rotate(glm::radians(-270.0f), vec3(1.0f,0.0f,0.0f)));
	//glmPrintM4(glmrot, "GLM rot");
	//glm::quat glmqm= glm::quat_cast(glmrot);
	//glmPrintQ(glmqm,"glm matrix from Q");

	//glm::mat4 glmRot = glm::toMat4(glmqm);
	//glmPrintM4(glmRot,"glm rotation Matrix from Q");
	//

	//Quaternion q3 = QMath::angleAxisRotation(-90.0,Vec3(1.0f,0.0f,0.0f));
	//q3.print("my Quat");
	//glm::quat myQuaternion = glm::angleAxis(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//glmPrintQ(myQuaternion, "glm Quat");


	//
	/// Lets say I have a unit vector along the x-axis 1,0,0. 
	///*Rotate 45.0 degree around the z-axis
	/// The resulting vector should be 0.70711, 0.70711, 0.0 
	/// Let's test this in every way I can think of
	Vec3 v(1.0, 0.0, 0.0);
	Quaternion q = QMath::angleAxisRotation(90.0,Vec3(0.0,1.0,0.0));
	Vec3 v2 = q * v * ~q;
	v2.print("rotate");
	/*Euler e2 = EMath::toEuler(q);
	e2.print("from Q");*/

	//q.print("The rotation Quaternion");
	//Euler e(0.0, 0.0, 45.0);

	//Quaternion qe = QMath::toQuaternion(e);
	//
	//qe.print("from Euler");
	//Vec3 v2 = qe * v * ~qe;
	//v2.print("The slow way");



	//Vec3 v3 = QMath::rotate(v, qe);
	//v3.print("faster way");

	//Matrix3 m3 = MMath::toMatrix3(qe);
	//Vec3 v4 = m3 * v;
	//v4.print("Mat3");

	//Matrix4 m4 = MMath::toMatrix4(qe);
	//Vec3 v5 = m4 * v;
	//v5.print("Mat4");

	//Quaternion q2 = QMath::angleAxisRotation(90.0, Vec3(0.0, 0.0, 1.0));
	//q2 = QMath::pow(q2, 0.5);
	//Vec3 v6 = QMath::rotate(v, q2);
	//v6.print("Using the pow function");

	//printf("Magnitude of q \n%f\n", QMath::magnitude(q));
	//Quaternion conj_q = QMath::conjugate(q);
	//conj_q.print("conjugate of q");

	//Quaternion inv_q = QMath::inverse(q);
	//inv_q.print("inv of q");

	//Quaternion q4 = q * inv_q;
	//q4.print("q * q-1 is the identity");

	Quaternion q1(0.0, Vec3(0.0,1.0,0.0));
	Quaternion q2(0.0, Vec3(0.0, 0.0, 1.0));
	Quaternion q3 = q1 * q2;
	q3.print();

}


void inverseTestMat4(){
	const string name = " inverseTest";
	Matrix4 rot = MMath::rotate(90.0f, Vec3(0.0f,1.0f,0.0f));
	Matrix4 invRot = MMath::inverse(rot);
	Matrix4 product4 = rot * invRot;
	bool test0 = compare(product4, Matrix4(), 1.0e-6f);
	

	Matrix3 rot3 = MMath::rotate(45.0f, Vec3(0.0f, 1.0f, 0.0f));
	Matrix3 invRot3 = MMath::inverse(rot);
	Matrix3 product3 = rot * invRot;
	bool test1 = compare(product3, Matrix3(), 1.0e-6f);

	if (test0 && test1) {
		printPassedOrFailed(true, name);
	}
	else {
		printPassedOrFailed(false, name);
		product4.print("should have been the Identity matrix");
		product3.print();
	}
}


void rotationIsOrthogonal() {
	const string name = " rotationIsOrthogonal";
	Matrix4 M = MMath::rotate(180.0f, Vec3(0, 1, 0));
	Vec4 v0 = M.getColumn(Matrix4::Colunm::zero);
	Vec4 v1 = M.getColumn(Matrix4::Colunm::one);
	Vec4 v2 = M.getColumn(Matrix4::Colunm::two);
	Vec4 v3 = M.getColumn(Matrix4::Colunm::three);
	bool test0 = compare(VMath::dot(v1, v0), 0.0f, 1.0e-6f);
	bool test1 = compare(VMath::dot(v2, v0), 0.0f, 1.0e-6f);
	bool test2 = compare(VMath::dot(v3, v0), 0.0f, 1.0e-6f);
	if (test0 && test1 && test2) {
		printPassedOrFailed(true, name);
	}
	else {
		printPassedOrFailed(false, name);
	}
}


void randomizerTest() {
	Randomizer r;
	ofstream myfile;
	myfile.open("data.csv");
	for (double i = 0.0; i < 512.0; i++) {
		double val = r.box_muller(0.0, 2.0);
		myfile << i << "," << val << "\n";
	}
	myfile.close();
}

void viewportNDCTest() {
	Matrix4 m = MMath::viewportNDC(1024, 1024);
	m.print();
	Vec3 pos0(0, 0, 0);
	Vec3 result0 = m * pos0;
	result0.print();

	Vec3 pos1(-1, 1, 1);
	Vec3 result1 = m * pos1;
	result1.print();
}

void multiplyMatrixTest() {
	const string name = " multiplyMatrixTest";
	Matrix4 tmSSF = MMath::translate(10.0f, 10.0f, 10.0f);
	Matrix4 rmSSF = MMath::rotate(90.0f, 0.0f, 1.0f, 0.0f);
	Matrix4 smSSF = MMath::scale(0.75f, 0.75f, 0.75f);
	Matrix4 resultSSF = tmSSF * rmSSF * smSSF;

	glm::mat4 mt = glm::translate(glm::vec3(10.0f, 10.0f, 10.0f));
	glm::mat4 mr = glm::rotate(glm::radians(90.0f), vec3(0, 1.0f, 0));
	glm::mat4 ms = glm::scale(glm::vec3(0.75f, 0.75f, 0.75f));
	glm::mat4 result = mt * mr * ms;
	bool comparison = compare(resultSSF, result, 1.0e-6f);
	if(comparison == true) {
		printPassedOrFailed(true, name);
	}
	else{ 
		printPassedOrFailed(false, name);
	}
}

void vec3MultiplyMat4Test() {
	Matrix4 translate = MMath::rotate(90.0, 0.0, 1.0,0.0);
	Vec3 pos(5.0, 0.0, 0.0);
	Vec4 xxx = pos;
	xxx.print();
	Vec3 result = translate * pos;
	result.print();
}

void rotationTest(){
	mat4 rot2 = rotate(mat4(), 3.141592654f/2.0f, vec3(1.0f,0.0f,0.0f));
	float  m[16] = {0.0};

	const float *pSource = (const float*)glm::value_ptr(rot2);
	for (int i = 0; i < 16; ++i)
		m[i] = pSource[i];
	printf("%1.8f %1.8f %1.8f %1.8f\n%1.8f %1.8f %1.8f %1.8f\n%1.8f %1.8f %1.8f %1.8f\n%1.8f %1.8f %1.8f %1.8f\n\n",
				m[0], m[4], m[8],  m[12],
				m[1], m[5], m[9],  m[13],
				m[2], m[6], m[10], m[14],
				m[3], m[7], m[11], m[15]);

}

void unOrthoTest() {
	/// Just seeing if I can deconstruct the the ortho matrix
	int w = 800, h = 600;
	Matrix4 ndc = MMath::viewportNDC(w,h);
	
	float xMax = 10.0, xMin = -10.0, yMax = 10.0, yMin = -10.0, zMax = 1.0, zMin = -10.0;
	Matrix4 ortho = MMath::orthographic(xMin, xMax, 
										yMin, yMax, 
										zMin, zMax);

	Matrix4 projection = ortho * ndc;
	projection.print();
	
	Matrix4 m;
	/// This is the ortho * ndc matrix broken down into its parts 
	Matrix4 m1 = MMath::scale(2.0f / (xMax - xMin), 2.0f / (yMax - yMin),-2.0f / (zMax - zMin));
	Matrix4 m2 = MMath::translate( -(xMax + xMin) / (xMax - xMin), -(yMax + yMin) / (yMax - yMin), -(zMax + zMin) / (zMax - zMin)); 
	Matrix4 m3 = MMath::scale(1.0f, -1.0f, 1.0f);
	Matrix4 m4 = MMath::scale(float(w)/2.0f, float(h)/2.0f, 1 - 0);
	Matrix4 m5 = MMath::translate(float(w)/2.0f,float(h)/2.0f, 0);

	/// Here they are in their inverse 
	Matrix4 m6 = MMath::inverse(m1);
	Matrix4 m7 = MMath::translate( (xMax + xMin) / (xMax - xMin), (yMax + yMin) / (yMax - yMin), (zMax + zMin) / (zMax - zMin)); 
	Matrix4 m8 = MMath::scale(1.0f, -1.0f, 1.0f);
	Matrix4 m9 = MMath::inverse(MMath::scale(float(w)/2.0f, float(h)/2.0f, 1 - 0));
	Matrix4 m10 = MMath::translate(-float(w)/2.0f,-float(h)/2.0f, 0);

	m = m1*m2*m3*m4*m5;  /// creates the ortho * ndc
	m *= m10 *m9 *m8 *m7 *m6; /// Now back out 
	m.print(); /// Should be an identity matrix
	/// It is!!!
		
	Matrix4 invOrtho = MMath::unOrtho(projection );
	invOrtho.print();
	Vec3 v1(400.0,300.0,0.0);
	Vec3 v2(10.0,0.0,10.0);
	Vec3 result1 = invOrtho  * v1;
	result1.print();	
}

void dqTranslateAlongLineTest() {
	const string name = " dqTranslateAlongLineTest";
	const float epsilon = VERY_SMALL * 1.0f;
	float diffMag;

	Vec4 point1(-1, -1, -1, 1);
	Vec4 point2(1, 1, 1, 1);
	DualQuat line = point1 & point2;
	float distanceAlongLine = 5.0f;
	DualQuat dqT = DQMath::translateAlongLine(distanceAlongLine, line);
	Vec4 pointToTranslate(0, 0, 0, 1);
	Vec4 translatedPoint = DQMath::rigidTransformation(dqT, pointToTranslate);

	// How about doing the same thing with matrices?
	Vec3 translationVector = point2 - point1;
	// Scale to match distance
	translationVector = distanceAlongLine * VMath::normalize(translationVector);
	Matrix4 T = MMath::translate(translationVector);
	Vec4 translatedPointUsingMat = T * pointToTranslate;

	bool test0 = false;
	diffMag = VMath::mag(translatedPoint - translatedPointUsingMat);
	if (diffMag < epsilon) {
		test0 = true;
	}

	// Try again with different points and distances
	point1.set(0.0f, -5.0f, 0.0f, 1.0f);
	point2.set(0.0f, +5.0f, 0.0f, 1.0f);
	line = point1 & point2;
	distanceAlongLine = 10.2f;
	pointToTranslate.set(-15.0f, 9.8f, 23.0f, 1.0f);
	dqT = DQMath::translateAlongLine(distanceAlongLine, line);
	translatedPoint = DQMath::rigidTransformation(dqT, pointToTranslate);

	translationVector = point2 - point1;
	translationVector = distanceAlongLine * VMath::normalize(translationVector);
	T = MMath::translate(translationVector);
	translatedPointUsingMat = T * pointToTranslate;

	bool test1 = false;
	diffMag = VMath::mag(translatedPoint - translatedPointUsingMat);
	if (diffMag < epsilon) {
		test1 = true;
	}

	bool flag = test0 && test1;
	printPassedOrFailed(flag, name);
}

void lookAtTest(){
	const string name = " lookAtTest";
	glm::mat4 mt = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f),
								glm::vec3(0.0f, 1.0f, 1.0f), 
								glm::vec3(0.0f, 1.0f, 0.0f));
	
	Matrix4 lookat = MMath::lookAt(Vec3(0.0f,0.0f,-10.0f), 
								Vec3(0.0f,1.0f,1.0f), 
								Vec3(0.0f,1.0f,0.0f));
	bool test0 = compare(lookat, mt, 1.0e-6f);

	mt = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	lookat = MMath::lookAt(Vec3(0.0f, 0.0f, -10.0f),
		Vec3(1.0f, 1.0f, 1.0f),
		Vec3(0.0f, 1.0f, 0.0f));

	bool test1 = compare(lookat, mt, 1.0e-6f);
	

	if (test0 && test1) {
		printPassedOrFailed(true, name);
	}
	else {
		printPassedOrFailed(false, name);
	}
}
void FFT_Test(){
	constexpr int SAMPLE_SIZE = 512;
	FILE *fp;

	float data[2 * SAMPLE_SIZE]{};
	float orig_data[2 * SAMPLE_SIZE]{};
	float transformed[2 * SAMPLE_SIZE]{};

	/// Change this as you will, keep it under the Nyquist frequency (1/2*step)
	float freq = 2.0f;
	float theta = 0.0f;
	float step = 2.0f * FLOAT_PI / (float)SAMPLE_SIZE;

	Randomizer r; /// I'll use this to create some noise

	
	/// Create a data sample SAMPLE_SIZE long times 2 (real and imaginary components)
	for (int i = 0; i < 2 * SAMPLE_SIZE; i += 2){
		data[i] = cos(theta * freq) + 0.7f*cos(theta * freq * 3) + (float) r.box_muller(0.0, 0.5); /// real
		data[i + 1] = 0.0f;									  ///img
		theta += step;
	}


	/// Just make a copy of the original data
	memcpy(orig_data, data, 2 * SAMPLE_SIZE * sizeof(float));


	/// Now do the FFT on the noisy data
	Fourier::fft(data, 2 * SAMPLE_SIZE, Fourier::DIRECTION::FORWARD);

	/// Keep a copy of the transformed data
	memcpy(transformed, data, 2 * SAMPLE_SIZE * sizeof(float));

	
	/// A cheesy version of a filter
	//for (int i = 0; i < 2 * SAMPLE_SIZE; i++){
	//if (abs(data[i] < 100.0f)) data[i] = 0.0f;
	//}

	
	/// Now do the reverse transform then renormalize
	Fourier::fft(data, 2 * SAMPLE_SIZE, Fourier::DIRECTION::REVERSE);

	/// Re-normalize the data
	for (int i = 0; i < 2 * SAMPLE_SIZE; i++){
		data[i] *= 1.0f / float(SAMPLE_SIZE);
	}

	/// Write it all out in files
	if (fopen_s(&fp, "0.orig_data.csv", "w") != 0){
		printf("Can't open file\n");
		return;
	}
	for (int i = 0; i < 2 * SAMPLE_SIZE; i += 2){
		fprintf(fp, "%f, %f\n", orig_data[i], orig_data[i + 1]);
	}
	fclose(fp);



	if (fopen_s(&fp, "1.transformed.csv", "w") != 0){
		printf("Can't open file\n");
		return;
	}
	for (int i = 0; i < 2 * SAMPLE_SIZE; i += 2){
		fprintf(fp, "%f, %f\n", transformed[i], transformed[i + 1]);
	}
	fclose(fp);


	if (fopen_s(&fp, "2.orig&reverse.csv", "w") != 0){
		printf("Can't open file\n");
		return;
	}
	for (int i = 0; i < 2 * SAMPLE_SIZE; i += 2){
		fprintf(fp, "%f, %f, %f, %f\n", orig_data[i], orig_data[i + 1], data[i], data[i + 1]);
	}
	fclose(fp);


}

void dqGetRotationTranslationTest() {
	const string name = " dqGetRotationTranslationTest";
	// NOTE: epsilon seems sensitive to the translation magnitude
	float epsilon = VERY_SMALL * 1000;

	float angleDeg = 250;
	Vec3 axis = VMath::normalize(Vec3(1, 2, -1));
	Vec3 translation(3.5f, 210.3f, -500.2f);

	DualQuat R(angleDeg, axis);
	DualQuat T(translation);

	DualQuat TR = T * R;
	DualQuat RT = R * T;

	// What was the original rotation?
	DualQuat R_extracted_from_TR = DQMath::getRotationDualQuat(TR);
	DualQuat T_extracted_from_TR = DQMath::getTranslationDualQuat(TR);
	DualQuat R_extracted_from_RT = DQMath::getRotationDualQuat(RT);
	DualQuat T_extracted_from_RT = DQMath::getTranslationDualQuat(RT);

	// Does this do the same thing to a vector?
	Vec4 v(1, 2, -5, 1);
	Vec4 v_transformed;
	Vec4 v_transformed_with_extracted_TR_dq;
	Vec4 v_transformed_with_extracted_RT_dq;
	float diffMag;

	// Test rotation
	v_transformed = DQMath::rigidTransformation(R, v);
	v_transformed_with_extracted_TR_dq = DQMath::rigidTransformation(R_extracted_from_TR, v);
	v_transformed_with_extracted_RT_dq = DQMath::rigidTransformation(R_extracted_from_RT, v);

	bool test0 = false;
	diffMag = VMath::mag(v_transformed - v_transformed_with_extracted_TR_dq);
	if (diffMag < epsilon) {
		test0 = true;
	}

	bool test1 = false;
	diffMag = VMath::mag(v_transformed - v_transformed_with_extracted_RT_dq);
	if (diffMag < epsilon) {
		test1 = true;
	}

	// Test translation
	v_transformed = DQMath::rigidTransformation(T, v);
	v_transformed_with_extracted_TR_dq = DQMath::rigidTransformation(T_extracted_from_TR, v);

	bool test2 = false;
	diffMag = VMath::mag(v_transformed - v_transformed_with_extracted_TR_dq);
	if (diffMag < epsilon) {
		test2 = true;
	}

	// To test the RT case for translations, let's see if we can match the original transforms
	// When we extract R and T from a dual quat, they are formed as a T * R transform 
	DualQuat TR_built_from_RT = T_extracted_from_RT * R_extracted_from_RT;
	Vec4 v_transformed_RT = DQMath::rigidTransformation(RT, v);
	Vec4 v_transformed_RT_extracted = DQMath::rigidTransformation(TR_built_from_RT, v);

	bool test3 = false;
	diffMag = VMath::mag(v_transformed_RT - v_transformed_RT_extracted);
	if (diffMag < epsilon) {
		test3 = true;
	}

	bool flag = test0 && test1 && test2 && test3;
	printPassedOrFailed(flag, name);
}

void dualQuatMatrixTest() {
	const string name = " dualQuatMatrixTest";
	const float epsilon = VERY_SMALL * 1000.0f;

	// Let's try a crazy matrix with lots of rotates and translates like this:
	// R3 * R2 * T3 * T2 * R1 * T1

	float angleDeg1 = 25.0f;
	float angleDeg2 = -15.2f;
	float angleDeg3 = 125.0f;

	Vec3 axis1 = VMath::normalize(Vec3(1, 2, -1));
	Vec3 axis2 = VMath::normalize(Vec3(0, 2, 5));
	Vec3 axis3 = VMath::normalize(Vec3(1, 1, 1));

	Vec3 translation1(1, 2, 4);
	Vec3 translation2(-21.5f, 22.0f, -1.1f);
	Vec3 translation3(7.5f, -12.0f, 101.1f);

	// Make matrices
	Matrix4 R1_mat = MMath::rotate(angleDeg1, axis1);
	Matrix4 R2_mat = MMath::rotate(angleDeg2, axis2);
	Matrix4 R3_mat = MMath::rotate(angleDeg3, axis3);
	Matrix4 T1_mat = MMath::translate(translation1);
	Matrix4 T2_mat = MMath::translate(translation2);
	Matrix4 T3_mat = MMath::translate(translation3);

	// Make Dual Quats
	DualQuat R1_dq = DQMath::rotate(angleDeg1, axis1);
	DualQuat R2_dq = DQMath::rotate(angleDeg2, axis2);
	DualQuat R3_dq = DQMath::rotate(angleDeg3, axis3);
	DualQuat T1_dq = DQMath::translate(translation1);
	DualQuat T2_dq = DQMath::translate(translation2);
	DualQuat T3_dq = DQMath::translate(translation3);

	// Make a crazy transform
	Matrix4  transform_mat = R3_mat * R2_mat * T3_mat * T2_mat * R1_mat * T1_mat;
	DualQuat transform_dq = R3_dq * R2_dq * T3_dq * T2_dq * R1_dq * T1_dq;

	Matrix4 transform_dq_to_mat = MMath::toMatrix4(transform_dq);

	// Do these matrices do the same thing to a vector?
	Vec3 v(1, 2, -3);

	Vec3 vTransformed_mat = transform_mat * v;
	Vec3 vTransformed_dq_to_mat = transform_dq_to_mat * v;

	bool test0 = false;
	float diffMag = VMath::mag(vTransformed_mat - vTransformed_dq_to_mat);
	if (diffMag < epsilon) {
		test0 = true;
	}

	// What if we inverse them?
	Matrix4  transform_mat_inversed = MMath::inverse(transform_mat);
	DualQuat transform_dq_inversed = DQMath::inverse(transform_dq);
	Matrix4  transform_dq_to_mat_inversed = MMath::toMatrix4(transform_dq_inversed);

	vTransformed_mat = transform_mat_inversed * v;
	vTransformed_dq_to_mat = transform_dq_to_mat_inversed * v;

	bool test1 = false;
	diffMag = VMath::mag(vTransformed_mat - vTransformed_dq_to_mat);
	if (diffMag < epsilon) {
		test1 = true;
	}

	bool flag = test0 && test1;
	printPassedOrFailed(flag, name);
}

void dqConstructorTest() {
	const string name = " dqConstructorTest";
	float epsilon = VERY_SMALL * 10;
	float diffMag;

	float angleDeg = 180;
	Vec3 axis = VMath::normalize(Vec3(1, 0, 0));
	Vec3 translation(2, 0, 0);

	// What happens if we rotate THEN translate the following vector?
	Vec3 v(0, 1, 0);

	// We know Matrices work. Start with those
	Matrix4 R = MMath::rotate(angleDeg, axis);
	Matrix4 T = MMath::translate(translation);
	// T * R does a rotate then translate
	Matrix4 matTransform = T * R;
	Vec3 vTransformedWithMat = matTransform * v;

	// Do the same with the Dual Quat constructor that builds rotation THEN translation
	DualQuat dqTransform = DualQuat(angleDeg, axis, translation);
	Vec4 v4d = Vec4(v);
	Vec4 v4dTransformedWithDq = DQMath::rigidTransformation(dqTransform, v4d);
	Vec3 vTransformedWithDq = Vec3(v4dTransformedWithDq);

	diffMag = VMath::mag(vTransformedWithMat - vTransformedWithDq);

	bool flag = diffMag < epsilon;
	printPassedOrFailed(flag, name);

}

void dualQuatTest() {
	const string name = " dualQuatTest";
	const float epsilon = VERY_SMALL * 10.0f;
	// Testing our dual quats against GLMs
	// Our dual quats transform a vector like this:
	// newVec4 = DQMath::rigidTransformation(dq, oldVec4);
	//
	// GLM seems to transform vectors like this: 
	// Looks strange, as I  thought we're supposed to do the sandwich with dqs? It's probably happening under the hood
	// newVec4Glm = dqGlm * oldVec4Glm

	glm::vec4 v4Glm(1, 2, -3, 1);
	Vec4 v4(v4Glm.x, v4Glm.y, v4Glm.z, v4Glm.w);

	glm::vec4 v4_transformedGlm;
	Vec4 v4_transformed;
	Vec4 v4_glmConvertedToOurs;

	float diffMag;

	// Identity tests
	DualQuat T = DQMath::translate(Vec3(0, 0, 0));
	DualQuat R = DQMath::rotate(0.0f, Vec3(0, 1, 0));
	DualQuat identity = T * R;

	glm::quat rotationQuaternion = glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 translationVector(0.0f, 0.0f, 0.0f);
	glm::dualquat glmIdeniity(rotationQuaternion, translationVector);
	//glmPrintDQ( glmIdeniity, "GLM's identity (I think) ");

	v4_transformed = DQMath::rigidTransformation(identity, v4);
	v4_transformedGlm = glmIdeniity * v4Glm;
	//glmPrintV4(v4_transformedGlm, "Transforming a point using glm's identity dual quat");
	//v4_transformed.print("Now our version");

	bool test0 = false;
	v4_glmConvertedToOurs.set(v4_transformedGlm.x, v4_transformedGlm.y, v4_transformedGlm.z, v4_transformedGlm.w);
	diffMag = VMath::mag(v4_glmConvertedToOurs - v4_transformed);
	if (diffMag < epsilon) {
		test0 = true;
	}
	//printf("\n\n");

	/// Pure Translate test 
	DualQuat translate2(Vec3(10, 0, 0));
	//translate2.print("Translate 10 units along x");

	glm::quat rotationQuaternion2 = glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 translationVector2(10.0f, 0.0f, 0.0f);
	glm::dualquat glmTranslate2(rotationQuaternion2, translationVector2);
	//glmPrintDQ(glmTranslate2, "GLM tranlate by 10");
	v4_transformed = DQMath::rigidTransformation(translate2, v4);
	v4_transformedGlm = glmTranslate2 * v4Glm;
	//glmPrintV4(v4_transformedGlm, "Transforming a point using glm's translate 10 along x dual quat");
	//v4_transformed.print("Now our version");

	bool test1 = false;
	v4_glmConvertedToOurs.set(v4_transformedGlm.x, v4_transformedGlm.y, v4_transformedGlm.z, v4_transformedGlm.w);
	diffMag = VMath::mag(v4_glmConvertedToOurs - v4_transformed);
	if (diffMag < epsilon) {
		test1 = true;
	}

	//printf("\n\n");

	// Pure Rotation test
	DualQuat pureRotate = DualQuat(QMath::angleAxisRotation(90.0f, Vec3(0.0f, 1.0f, 0.0f)));
	//pureRotate.print("90 rotate along Y");

	glm::quat rotationQuaternion3 = glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 translationVector3(0.0f, 0.0f, 0.0f);
	glm::dualquat glmTranslate3(rotationQuaternion3, translationVector3);
	//glmPrintDQ(glmTranslate3, "GLM 90 along Y");

	v4_transformed = DQMath::rigidTransformation(pureRotate, v4);
	v4_transformedGlm = glmTranslate3 * v4Glm;
	//glmPrintV4(v4_transformedGlm, "Transforming x vector using glm's rotate 90 abt y dual quat");
	//v4_transformed.print("Now our version");

	bool test2 = false;
	v4_glmConvertedToOurs.set(v4_transformedGlm.x, v4_transformedGlm.y, v4_transformedGlm.z, v4_transformedGlm.w);
	diffMag = VMath::mag(v4_glmConvertedToOurs - v4_transformed);
	if (diffMag < epsilon) {
		test2 = true;
	}

	//printf("\n\n");

	// Rotate then translate test
	float angleDeg = 33.0f;
	Vec3 axis = VMath::normalize(Vec3(1, 3, -2));
	Vec3 translation(1.2f, -32.6f, 5.0f);
	DualQuat rotateThenTranslate = DualQuat(angleDeg, axis, translation);

	glm::quat rotationQuaternion4 = glm::angleAxis(glm::radians(angleDeg), glm::vec3(axis.x, axis.y, axis.z));
	glm::vec3 translationVector4(translation.x, translation.y, translation.z);
	glm::dualquat rotateThenTranslateGlm(rotationQuaternion4, translationVector4);

	v4_transformed = DQMath::rigidTransformation(rotateThenTranslate, v4);
	v4_transformedGlm = rotateThenTranslateGlm * v4Glm;
	//glmPrintV4(v4_transformedGlm, "Transforming using glm's rotate then translate dual quat");
	//v4_transformed.print("Now our version");

	bool test3 = false;
	v4_glmConvertedToOurs.set(v4_transformedGlm.x, v4_transformedGlm.y, v4_transformedGlm.z, v4_transformedGlm.w);
	diffMag = VMath::mag(v4_glmConvertedToOurs - v4_transformed);
	if (diffMag < epsilon) {
		test3 = true;
	}

	bool flag = test0 && test1 && test2 && test3;
	printPassedOrFailed(flag, name);
}

void dualQuatSlerpTest() {
	const string name = " dualQuatSlerpTest";
	const float epsilon = VERY_SMALL * 100;

	Vec3 startPos(-2, 0, 0);
	Vec3 endPos(5, 11, 0);
	float angleDeg = 180;
	Quaternion startRot = QMath::angleAxisRotation(0, Vec3(0, 1, 0));
	Quaternion endRot = QMath::angleAxisRotation(angleDeg, Vec3(0, 1, 0));
	DualQuat startDQ = DQMath::translate(startPos) * DQMath::rotate(startRot);
	DualQuat endDQ = DQMath::translate(endPos) * DQMath::rotate(endRot);
	DualQuat slerpDQStart = DQMath::slerp(startDQ, endDQ, 0.0f);
	DualQuat slerpDQMiddle = DQMath::slerp(startDQ, endDQ, 0.5f);
	DualQuat slerpDQEnd = DQMath::slerp(startDQ, endDQ, 1.0f);

	//startPos.print("Starting pos");
	//startRot.print("Starting rot");
	//endPos.print("Ending pos");
	//endRot.print("Ending rot");
	//std::cout << "***********************\n";
	//slerpDQStart.print("Dual Quat with t = 0");
	Vec3 posTzero = DQMath::getTranslation(slerpDQStart);
	//posTzero.print("pos t = 0");
	Quaternion rotTzero = DQMath::getRotation(slerpDQStart);
	//rotTzero.print("rot t = 0");
	bool passedPos1 = false;
	if (VMath::mag(posTzero - startPos) < epsilon) {
		passedPos1 = true;
	}
	bool passedRot1 = false;
	if (QMath::magnitude(rotTzero - startRot) < epsilon) {
		passedRot1 = true;
	}
	//std::cout << "***********************\n";
	//slerpDQMiddle.print("Slerp with t = 0.5");
	Vec3 posThalf = DQMath::getTranslation(slerpDQMiddle);
	//posThalf.print("pos t = 0.5");
	Quaternion rotThalf = DQMath::getRotation(slerpDQMiddle);
	//rotThalf.print("rot t = 0.5");
	bool passedPos2 = false;
	Quaternion middleRot = QMath::normalize(startRot + endRot);
	Vec3 middlePos = QMath::rotate(startPos, middleRot) + (endPos + startPos) / 2;
	if (VMath::mag(posThalf - middlePos) < epsilon) {
		passedPos2 = true;
	}
	bool passedRot2 = false;
	if (QMath::magnitude(rotThalf - middleRot) < epsilon) {
		passedRot2 = true;
	}
	//std::cout << "***********************\n";
	//slerpDQEnd.print("Slerp with t = 1");
	Vec3 posTone = DQMath::getTranslation(slerpDQEnd);
	//posTone.print("pos t = 1");
	Quaternion rotTone = DQMath::getRotation(slerpDQEnd);
	//rotTone.print("rot t = 1");
	bool passedPos3 = false;
	if (VMath::mag(posTone - endPos) < epsilon) {
		passedPos3 = true;
	}
	bool passedRot3 = false;
	if (QMath::magnitude(rotTone - endRot) < epsilon) {
		passedRot3 = true;
	}

	bool flag = passedPos1 && passedPos2 && passedPos3 &&
		passedRot1 && passedRot2 && passedRot3;
	printPassedOrFailed(flag, name);
}

void projectTest() {
	const string name = " projectTest";
	float epsilon = VERY_SMALL * 1;
	float diffMag;

	// Project a point onto a plane
	Vec4 point(-4.95f, 5.23f, 212.0f, 1.0f);
	// Flat plane at y = 2
	const float yPlane = 2;
	//Plane plane(Vec3(0, 1, 0), 2);
	Plane plane = Vec4(0, yPlane, 0, 1) & Vec4(1, yPlane, 0, 1) & Vec4(0, yPlane, 1, 1);
	Vec4 projectedPoint = PMath::project(point, plane);
	// The w component might not be one. Divide it out just in case
	projectedPoint = VMath::perspectiveDivide(projectedPoint);
	// Answer should be (point.x, yPlane, point.z)
	Vec4 correctAnswer(point.x, yPlane, point.z, 1);

	bool test0 = false;
	diffMag = VMath::mag(projectedPoint - correctAnswer);
	if (diffMag < epsilon) {
		test0 = true;
	}

	// Now project point onto a straight line going up through x = 10 and z = 0
	const float xValue = 10;
	const float zValue = 0;
	DualQuat line = Vec4(xValue, 0, zValue, 1) & Vec4(xValue, 1, zValue, 1);
	projectedPoint = DQMath::project(point, line);
	projectedPoint = VMath::perspectiveDivide(projectedPoint);
	// Answer should be (xValue, point.y, zValue)
	correctAnswer.set(xValue, point.y, zValue, 1);

	bool test1 = false;
	diffMag = VMath::mag(projectedPoint - correctAnswer);
	if (diffMag < epsilon) {
		test1 = true;
	}

	bool flag = test0 && test1;
	printPassedOrFailed(flag, name);
}

void dqLookAtTest() {
	const string name = " dqLookAtTest";
	float epsilon = VERY_SMALL * 1000;

	Vec4 eye = Vec4(0, 0, 20, 1); // camera is 20 units along the z-axis
	Vec4 at = Vec4(1, 0, 20, 1); // Looking to the right 
	Vec4 up = Vec4(0, 1, 0, 0);  // Up is along positive y

	// View transforms should do the same things to the following vector position
	Vec4 v(1.0f, 2.0f, -15.6f, 1.0f);
	glm::vec4 v_glm(v.x, v.y, v.z, v.w);

	float diffMag;
	Vec4 v_TR_inversed_dq;
	Vec4 v_lookAt_dq;
	Vec4 v_lookAt_mat;
	Vec4 v_lookAt_mat_glm;
	glm::vec4 v_glm_lookAt_mat_glm;

	DualQuat viewDq1 = DQMath::lookAt(eye, at, up);
	v_lookAt_dq = DQMath::rigidTransformation(viewDq1, v);

	// check against building the view matrix using R^(-1) * T^(-1)
	// We start looking down the -z. So look to the right is a -90 deg rot about y axis
	float rotationAngleDeg = -90.0f;
	Vec3 rotationAxis = Vec3(0.0f, 1.0f, 0.0f);
	Quaternion cameraOrientation = QMath::angleAxisRotation(rotationAngleDeg, rotationAxis);
	DualQuat viewDq2 = DQMath::rotate(QMath::inverse(cameraOrientation)) * DQMath::translate(-eye);
	v_TR_inversed_dq = DQMath::rigidTransformation(viewDq2, v);

	// And check against the original lookAts
	Matrix4 view = MMath::lookAt(Vec3(eye), Vec3(at), Vec3(up));
	v_lookAt_mat = view * v;

	bool test0 = false;
	diffMag = VMath::mag(v_lookAt_dq - v_lookAt_mat);
	if (diffMag < epsilon) {
		test0 = true;
	}

	glm::mat4 mt = glm::lookAt(
		glm::vec3(eye.x, eye.y, eye.z),
		glm::vec3(at.x, at.y, at.z),
		glm::vec3(up.x, up.y, up.z));
	v_glm_lookAt_mat_glm = mt * v_glm;
	v_lookAt_mat_glm.set(v_glm_lookAt_mat_glm.x, v_glm_lookAt_mat_glm.y, v_glm_lookAt_mat_glm.z, v_glm_lookAt_mat_glm.w);

	// Seems to be a discrepancy between MMath::lookAt and glm::lookAt?
	//glmPrintM4(mt, "GLM's lookAt");
	//view.print("MMath's lookAt");

	bool test1 = false;
	diffMag = VMath::mag(v_lookAt_dq - v_lookAt_mat_glm);
	if (diffMag < epsilon) {
		test1 = true;
	}

	bool test2 = false;
	diffMag = VMath::mag(v_lookAt_mat - v_lookAt_mat_glm);
	if (diffMag < epsilon) {
		test2 = true;
	}

	bool test3 = false;
	diffMag = VMath::mag(v_lookAt_dq - v_TR_inversed_dq);
	if (diffMag < epsilon) {
		test3 = true;
	}


	// Now check again, but up is along positive z now
	up = Vec4(0, 0, 1, 0);
	viewDq1 = DQMath::lookAt(eye, at, up);
	view = MMath::lookAt(Vec3(eye), Vec3(at), Vec3(up));
	mt = glm::lookAt(
		glm::vec3(eye.x, eye.y, eye.z),
		glm::vec3(at.x, at.y, at.z),
		glm::vec3(up.x, up.y, up.z));

	// Seems to be a discrepancy between MMath::lookAt and glm::lookAt?
	//printf("\n");
	//glmPrintM4(mt, "GLM's lookAt");
	//view.print("MMath's lookAt");

	// What happens to the original vector now?
	v_lookAt_dq = DQMath::rigidTransformation(viewDq1, v);
	v_lookAt_mat = view * v;
	v_glm_lookAt_mat_glm = mt * v_glm;
	v_lookAt_mat_glm.set(v_glm_lookAt_mat_glm.x, v_glm_lookAt_mat_glm.y, v_glm_lookAt_mat_glm.z, v_glm_lookAt_mat_glm.w);

	bool test4 = false;
	diffMag = VMath::mag(v_lookAt_dq - v_lookAt_mat);
	if (diffMag < epsilon) {
		test4 = true;
	}

	bool test5 = false;
	diffMag = VMath::mag(v_lookAt_dq - v_lookAt_mat_glm);
	if (diffMag < epsilon) {
		test5 = true;
	}

	bool test6 = false;
	diffMag = VMath::mag(v_lookAt_mat - v_lookAt_mat_glm);
	if (diffMag < epsilon) {
		test6 = true;
	}

	bool flag = test0 && test1 && test2 && test3 && test4 && test5 && test6;
	printPassedOrFailed(flag, name);
}

void planeTest() {
	const string name = " planeTest";
	const float epsilon = VERY_SMALL * 10.0f;
	/*Plane p1(2.0f, -2.0f, 5.0f, 8.0f);
	p1.print();
	Vec3 v = Vec3(4.0f, -4.0f, 3.0f);
	v.print();
	float distance = PMath::distance(v, p1);
	printf("%f vs. 6.79\n", distance);
	Plane p2 = PMath::normalize(p1);
	p2.print();
	float distance2 = PMath::distance(v, p2);
	printf("%f vs. 6.79\n", distance2);

	Plane p3(1, 2, 2, -6);
	Vec3 v3(-1, -2, -3);
	float distance3 = PMath::distance(v3, p3);
	printf("%f vs. %f\n", distance3, -17.0/3.0);
	Plane p4 = PMath::normalize(p3);
	p4.print();
	float distance4 = PMath::distance(v3, p4);
	printf("%f vs. %f\n", distance4, -17.0 / 3.0);*/

	Vec3 eye = Vec3(0.0f, 0.0f, 8.0f);
	float perspectiveArgumentZNear = 1.0f;
	float perspectiveArgumentZFar = 10.0f;

	Matrix4 proj = MMath::perspective(52.8f, 1.0f, perspectiveArgumentZNear, perspectiveArgumentZFar) *
		MMath::lookAt(eye, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));

	// Woah, looks like SSF is extracting the near and far clipping planes here
#define INDEX(column,row) (proj[(row-1) * 4 + (column-1)])


	Plane near(INDEX(4, 1) + INDEX(3, 1),
		INDEX(4, 2) + INDEX(3, 2),
		INDEX(4, 3) + INDEX(3, 3),
		INDEX(4, 4) + INDEX(3, 4));
	near = PMath::normalize(near);
	Plane far(INDEX(4, 1) - INDEX(3, 1),
		INDEX(4, 2) - INDEX(3, 2),
		INDEX(4, 3) - INDEX(3, 3),
		INDEX(4, 4) - INDEX(3, 4));
	far = PMath::normalize(far);

	Vec3 v5(0.0, 0.0, 0.0);
	float distance5 = fabs(PMath::distance(eye, near));
	bool test1 = false;
	if (fabs(distance5 - perspectiveArgumentZNear) < epsilon) {
		test1 = true;
	}

	distance5 = fabs(PMath::distance(eye, far));
	bool test2 = false;
	if (fabs(distance5 - perspectiveArgumentZFar) < epsilon) {
		test2 = true;
	}

	// Weird how a plane's inverse is the same thing. Gotta check i've done this right tho...
	Plane p1(1, 0, 0, 4);
	Plane p1Inverse = PMath::inverse(p1);
	bool test3 = false;
	Plane pDiff = p1 - p1Inverse;
	if (fabs(pDiff.x) < epsilon && fabs(pDiff.y) < epsilon && fabs(pDiff.z) < epsilon && fabs(pDiff.d) < epsilon) {
		test3 = true;
	}

	// Normalize a plane by dividing it by the magnitude of the normal
	Vec3 normal(4, 0, 0);
	Plane p2(4, 0, 0, 2);
	Plane p2Normalized1 = PMath::normalize(p2);
	Plane p2Normalized2 = p2 / VMath::mag(normal);
	bool test4 = false;
	pDiff = p2Normalized1 - p2Normalized2;
	if (fabs(pDiff.x) < epsilon && fabs(pDiff.y) < epsilon && fabs(pDiff.z) < epsilon && fabs(pDiff.d) < epsilon) {
		test4 = true;
	}

	Vec3 normalStart(0, 1, 0);
	Plane startPlane(normalStart, 0);

	Vec3 normalEnd(1, 0, 0);
	Plane endPlane(normalEnd, 0);

	Plane midPlane1 = PMath::normalize(PMath::midPlane(startPlane, endPlane));
	// Midplane should be halfway between starting and ending plane
	Vec3 normalMid = VMath::normalize((normalStart + normalEnd) / 2.0f);
	Plane midPlane2(normalMid, 0);
	bool test5 = false;
	pDiff = midPlane1 - midPlane2;
	if (fabs(pDiff.x) < epsilon && fabs(pDiff.y) < epsilon && fabs(pDiff.z) < epsilon && fabs(pDiff.d) < epsilon) {
		test5 = true;
	}

	bool flag = test1 && test2 && test3 && test4 && test5;
	printPassedOrFailed(flag, name);
}

void quadraticTest() {
	/// Two root solution 
	Roots root = Quadratic::findRoots(1.0f, -5.0f, 6.0f);
	root.print("Quadratic roots: should be 2.0,3.0");

	/// Another two root solution 
	root = Quadratic::findRoots(5.0f, 6.0f, 1.0f);
	root.print("Quadratic roots: should be -0.2,-1.0");

	/// One root solution 
	root = Quadratic::findRoots(1.0f, 4.0f, 4.0f);
	root.print("Quadratic roots: should be -2.0,-2.0");

	/// No solutions (all imaginary -1 + 2i, -1 - 2i)  
	root = Quadratic::findRoots(1.0f, 2.0f, 5.0f);
	root.print("Quadratic roots: 0, 0.0, 0.0,");
}

// VISUALIZED: https://github.com/ScottFielder/MathLibrary/blob/master/Images/raySphere.png
// REFERENCE: https://hamishtodd1.substack.com/p/sphere-circle-and-cylinder-intersections
// EXAMPLE: https://github.com/ScottFielder/MathLibrary/blob/master/Notes/Line_intersection_sphere.pdf
void raySphereTest() {
	const string name = " raySphereTest";
	const float epsilon = VERY_SMALL * 1.0f;
	float diffMag;

	const Vec3 sphereCentre = Vec3(3.0f, 0.0f, 0.0);
	const float sphereRadius = 1.0f;
	const Sphere s(sphereCentre, sphereRadius);

	/// Two roots 
	Ray r0(Vec3(0.0f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
	Roots root0 = RMath::intersection(r0, s);
	Vec3 intersectionPoint0_a;
	Vec3 intersectionPoint0_b;
	if (root0.numRoots > 0) {
		intersectionPoint0_a = r0.start + r0.direction * root0.firstRoot;
		intersectionPoint0_b = r0.start + r0.direction * root0.secondRoot;
	}

	/// One root 
	Ray r1(Vec3(0.0f, -1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
	Roots root1 = RMath::intersection(r1, s);
	Vec3 intersectionPoint1_a;
	Vec3 intersectionPoint1_b;
	if (root1.numRoots > 0) {
		intersectionPoint1_a = r1.start + r1.direction * root1.firstRoot;
		intersectionPoint1_b = r1.start + r1.direction * root1.secondRoot;
	}

	/// No roots - no intersection
	Ray r2(Vec3(0.0f, -3.0f, 0.0f), VMath::normalize(Vec3(1.0f, 0.5f, 0.0f)));
	Roots root2 = RMath::intersection(r2, s);
	Vec3 intersectionPoint2_a(-99, -99, -99);
	Vec3 intersectionPoint2_b(-99, -99, -99);
	if (root2.numRoots == 0) {
		intersectionPoint2_a.set(0, 0, 0);
		intersectionPoint2_b.set(0, 0, 0);
	}

	// Looking at the graph, I know what the answers should be;
	Vec3 correctIntersection0_a(2, 0, 0);
	Vec3 correctIntersection0_b(4, 0, 0);

	Vec3 correctIntersection1_a(3, -1, 0);
	Vec3 correctIntersection1_b(3, -1, 0);

	Vec3 correctIntersection2_a(0, 0, 0);
	Vec3 correctIntersection2_b(0, 0, 0);

	// Would be nice to do this with PGA too
	// I stumbled across this article that has a very nice way of doing line - sphere intersection using dual quats :
	// https://hamishtodd1.substack.com/p/sphere-circle-and-cylinder-intersections
	// written by Hamish Todd(he has some great PGA talks at GDC).
	// I tried out an example on paper using his method and it worked nicely for a simple set up.
	// I've attached photos of my scribbles at the top of the function.The first page is the one with a sketch of a line intersecting a sphere.
	DualQuat line0 = DQMath::normalize(Vec4(r0.start, 1) & Vec4(r0.direction, 0));
	DualQuat line1 = DQMath::normalize(Vec4(r1.start, 1) & Vec4(r1.direction, 0));
	DualQuat line2 = DQMath::normalize(Vec4(r2.start, 1) & Vec4(r2.direction, 0));

	Flector f0 = (line0 * Vec4(sphereCentre, 1));
	Flector f1 = (line1 * Vec4(sphereCentre, 1));
	Flector f2 = (line2 * Vec4(sphereCentre, 1));

	Plane M0 = f0.plane;
	Plane M1 = f1.plane;
	Plane M2 = f2.plane;

	Vec4 M0_grade3 = f0.point;
	Vec4 M1_grade3 = f1.point;
	Vec4 M2_grade3 = f2.point;

	float d0_squared = sphereRadius * sphereRadius - DQMath::mag(dual(M0_grade3) * dual(M0_grade3));
	float d1_squared = sphereRadius * sphereRadius - DQMath::mag(dual(M1_grade3) * dual(M1_grade3));
	float d2_squared = sphereRadius * sphereRadius - DQMath::mag(dual(M2_grade3) * dual(M2_grade3));

	// If d_squared > 0, 2 roots
	// If d_squared = 0, 1 roots
	// If d_squared < 0, 0 roots

	Vec4 intersectionPointPGA0_a(0, 0, 0, 1);
	Vec4 intersectionPointPGA0_b(0, 0, 0, 1);
	Vec4 intersectionPointPGA1_a(0, 0, 0, 1);
	Vec4 intersectionPointPGA1_b(0, 0, 0, 1);
	Vec4 intersectionPointPGA2_a(-99, -99, -99, 1);
	Vec4 intersectionPointPGA2_b(-99, -99, -99, 1);

	Plane e0(0, 0, 0, 1);

	// Should be two intersections for line0
	if (d0_squared > 0) {
		intersectionPointPGA0_a = line0 ^ (M0 - e0 * sqrt(d0_squared));
		intersectionPointPGA0_b = line0 ^ (M0 + e0 * sqrt(d0_squared));
	}
	// Divide out the w
	intersectionPointPGA0_a = VMath::perspectiveDivide(intersectionPointPGA0_a);
	intersectionPointPGA0_b = VMath::perspectiveDivide(intersectionPointPGA0_b);

	// Should be one intersection for line1
	if (fabs(d1_squared) < VERY_SMALL) {
		intersectionPointPGA1_a = line1 ^ (M1 - e0 * sqrt(d1_squared));
		intersectionPointPGA1_b = line1 ^ (M1 + e0 * sqrt(d1_squared));
	}
	// Divide out the w
	intersectionPointPGA1_a = VMath::perspectiveDivide(intersectionPointPGA1_a);
	intersectionPointPGA1_b = VMath::perspectiveDivide(intersectionPointPGA1_b);

	// Should be none for line2
	if (d2_squared < 0) {
		intersectionPointPGA2_a.set(0, 0, 0, 1);
		intersectionPointPGA2_b.set(0, 0, 0, 1);
	}

	// Time to test all intersection points with true values
	bool test0 = false;
	diffMag = VMath::mag(correctIntersection0_a - intersectionPoint0_a);
	if (diffMag < epsilon) {
		test0 = true;
	}

	bool test1 = false;
	diffMag = VMath::mag(correctIntersection0_b - intersectionPoint0_b);
	if (diffMag < epsilon) {
		test1 = true;
	}

	bool test2 = false;
	diffMag = VMath::mag(correctIntersection1_a - intersectionPoint1_a);
	if (diffMag < epsilon) {
		test2 = true;
	}

	bool test3 = false;
	diffMag = VMath::mag(correctIntersection1_b - intersectionPoint1_b);
	if (diffMag < epsilon) {
		test3 = true;
	}

	bool test4 = false;
	diffMag = VMath::mag(correctIntersection2_a - intersectionPoint2_a);
	if (diffMag < epsilon) {
		test4 = true;
	}

	bool test5 = false;
	diffMag = VMath::mag(correctIntersection2_b - intersectionPoint2_b);
	if (diffMag < epsilon) {
		test5 = true;
	}

	// Test the PGA versions too
	bool test6 = false;
	diffMag = VMath::mag(correctIntersection0_a - intersectionPointPGA0_a);
	if (diffMag < epsilon) {
		test6 = true;
	}

	bool test7 = false;
	diffMag = VMath::mag(correctIntersection0_b - intersectionPointPGA0_b);
	if (diffMag < epsilon) {
		test7 = true;
	}

	bool test8 = false;
	diffMag = VMath::mag(correctIntersection1_a - intersectionPointPGA1_a);
	if (diffMag < epsilon) {
		test8 = true;
	}

	bool test9 = false;
	diffMag = VMath::mag(correctIntersection1_b - intersectionPointPGA1_b);
	if (diffMag < epsilon) {
		test9 = true;
	}

	bool test10 = false;
	diffMag = VMath::mag(correctIntersection2_a - intersectionPointPGA2_a);
	if (diffMag < epsilon) {
		test10 = true;
	}

	bool test11 = false;
	diffMag = VMath::mag(correctIntersection2_b - intersectionPointPGA2_b);
	if (diffMag < epsilon) {
		test11 = true;
	}

	bool flag = test0 && test1 && test2 && test3 && test4 && test5 &&
		test6 && test7 && test8 && test9 && test10 && test11;
	printPassedOrFailed(flag, name);
}


void RayTest() {
	Vec3 v1(0.0f, 0.0f, 0.0f);
	Vec3 v2(1.0f, 0.0f, 0.0f);
	Ray ray(v1, v2);
	Vec3 v3 = ray.getPos(0.5f);
	v3.print();
	Plane plane(0.0f, 1.0f, 0.0f, 10.0f);
	//Vec3 intersection = RMath::rayPlaneIntersection(ray,plane);
	//intersection.print();
}



void flectorTest() {
	Flector f1;
	f1.plane = Plane(1.0f, 0.0f, 0.0f, 0.0f);
	f1.point = Vec4(0.0f, 1.0f, 0.0f, 1.0f);

	Flector f2;
	f2.plane = Plane(1.0f, 0.0f, 0.0f, 0.0f);
	f2.point = Vec4(0.0f, 1.0f, 0.0f, 1.0f);

	f1.print("Flector 1");
	f2.print("Flector 2");
	f1 += f2;
	f1.print("f1 after adding f2");
}



void intersectionTest() {
	Plane xPlane(1, 0, 0, 0);
	Plane yPlane(0, 1, 0, 0);;
	DualQuat dqIntersection = yPlane * xPlane;
	xPlane.print("x plane");
	yPlane.print("y plane");
	dqIntersection.print("intersection line of both planes");
}

void dualTest() {
	Plane xPlane(1, 0, 0, 0);
	Vec4 xPlaneDual = !xPlane;
	xPlane.print("x plane");
	xPlaneDual.print("the dual of the plane");
	std::cout << "***********************\n";
	Vec4 point(1, 2, 3, 1);
	Plane pointDual = !point;
	point.print("Original point");
	pointDual.print("Dual of the point");
	std::cout << "***********************\n";
	DualQuat dq = DQMath::rotate(QMath::angleAxisRotation(90, Vec3(1, 0, 0)));
	DualQuat dqDual = !dq;
	dq.print("Dual quaternion that rotates 90 degrees abt x");
	dqDual.print("Dual of the dual quaternion. Sounds weird like that");
}

void meetTest() {
	Plane yPlane(0, 1, 0, -5);
	DualQuat yLine(0, 0, 1, 0, 0, 0, 0, 0);
	yPlane.print("y plane");
	yLine.print("y line");
	Vec4 meetPoint = yPlane ^ yLine;
	meetPoint.print("They meet at this point");
	PMath::intersection(yPlane, yLine).print("Checking with PMath call too");
}

void joinTest() {
	Vec4 pointA(-5, -5, 0, 1);
	Vec4 pointB(-5, 5, 0, 1);
	DualQuat lineJoiningPoints = pointA & pointB;
	pointA.print("Point A");
	pointB.print("Point B");
	lineJoiningPoints.print("Line AB");
	Plane yPlane(0.0f, 1.0f, 0.0f, 0.0f);
	(yPlane ^ lineJoiningPoints).print("Line pierces y plane this this point");

}

void rotateTest() {
	const string name = " rotateTest";
	const float epsilon = VERY_SMALL * 10.0f;
	float diffMag;

	const Vec4 point(1, 2, -3, 1);

	const float angle1 = 32.0f;
	const float angle2 = 235.0f;
	const float angle3 = -52.0f;

	const Vec3 axis1 = VMath::normalize(Vec3(1, 2, -2));
	const Vec3 axis2 = VMath::normalize(Vec3(5, -2, 0));
	const Vec3 axis3 = VMath::normalize(Vec3(0, 2, 2));

	// Rotate the point three ways
	Matrix4 R1_mat = MMath::rotate(angle1, axis1);
	Matrix4 R2_mat = MMath::rotate(angle2, axis2);
	Matrix4 R3_mat = MMath::rotate(angle3, axis3);

	Quaternion R1_q = QMath::angleAxisRotation(angle1, axis1);
	Quaternion R2_q = QMath::angleAxisRotation(angle2, axis2);
	Quaternion R3_q = QMath::angleAxisRotation(angle3, axis3);

	DualQuat R1_dq = DQMath::rotate(angle1, axis1);
	DualQuat R2_dq = DQMath::rotate(angle2, axis2);
	DualQuat R3_dq = DQMath::rotate(angle3, axis3);

	Matrix4    transform_mat = R1_mat * R2_mat * R3_mat;
	Quaternion transform_q = R1_q * R2_q * R3_q;
	DualQuat   transform_dq = R1_dq * R2_dq * R3_dq;

	Vec4 point_tranformed_mat = transform_mat * point;
	Vec4 point_transformed_q = QMath::rotate(point, transform_q);
	Vec4 point_transformed_dq = DQMath::rigidTransformation(transform_dq, point);

	bool test0 = false;
	diffMag = VMath::mag(point_tranformed_mat - point_transformed_dq);
	if (diffMag < epsilon) {
		test0 = true;
	}

	bool test1 = false;
	diffMag = VMath::mag(point_transformed_q - point_transformed_dq);
	if (diffMag < epsilon) {
		test1 = true;
	}

	bool test2 = false;
	diffMag = VMath::mag(point_tranformed_mat - point_transformed_q);
	if (diffMag < epsilon) {
		test2 = true;
	}

	bool flag = test0 && test1 && test2;
	printPassedOrFailed(flag, name);
}

void translateTest() {
	string name = " translateTest";
	const float epsilon = VERY_SMALL * 1;
	float diffMag;

	const Vec4 point(-4, 2, 34, 1);

	const Vec3 translation1(12.0f, 2.0f, -3.0f);
	const Vec3 translation2(-54.0f, 62.4f, -0.001f);
	const Vec3 translation3(-3.0f, -7.0f, -10.0f);

	// Translate the point three ways
	Matrix4 T1_mat = MMath::translate(translation1);
	Matrix4 T2_mat = MMath::translate(translation2);
	Matrix4 T3_mat = MMath::translate(translation3);

	DualQuat T1_dq = DQMath::translate(translation1);
	DualQuat T2_dq = DQMath::translate(translation2);
	DualQuat T3_dq = DQMath::translate(translation3);

	Matrix4  transform_mat = T1_mat * T2_mat * T3_mat;
	DualQuat transform_dq = T1_dq * T2_dq * T3_dq;
	Vec3     transform_vec = translation1 + translation2 + translation3;

	Vec4 point_transformed_mat = transform_mat * point;
	Vec4 point_transformed_dq = DQMath::rigidTransformation(transform_dq, point);
	Vec4 point_transformed_vec = point + Vec4(transform_vec, 0.0f);

	bool test0 = false;
	diffMag = VMath::mag(point_transformed_mat - point_transformed_dq);
	if (diffMag < epsilon) {
		test0 = true;
	}

	bool test1 = false;
	diffMag = VMath::mag(point_transformed_dq - point_transformed_vec);
	if (diffMag < epsilon) {
		test1 = true;
	}

	bool test2 = false;
	diffMag = VMath::mag(point_transformed_mat - point_transformed_vec);
	if (diffMag < epsilon) {
		test2 = true;
	}

	bool flag = test0 && test1 && test2;
	printPassedOrFailed(flag, name);
}

void gradeTest() {
	DualQuat dq(1, 2, 3, 4, 5, 6, 7, 8);
	dq.print("whole dual quaternion");
	std::cout << "Grade 0 part (w part): " << DQMath::magGrade0(dq) << "\n";
	std::cout << "Grade 2 part (e23, e31, e12 parts): " << DQMath::magGrade2(dq) << " --> Check it matches " << VMath::mag(Vec3(2, 3, 4)) << "\n";
	std::cout << "Grade 2 part at infinity (e01, e02, e03 parts): " << DQMath::magGrade2Infinity(dq) << " --> Check it matches " << VMath::mag(Vec3(5, 6, 7)) << "\n";
	std::cout << "Grade 4 part (e0123 part): " << DQMath::magGrade4Infinity(dq) << "\n";
	DQMath::extractLine(dq).print("Line part of the dual quaternion");
}


void normalizeLineTest() {
	DualQuat dq(1, 2, 3, 4, 5, 6, 7, 8);
	dq.print("whole dual quaternion (Euclidean)");
	DualQuat normalized = DQMath::normalize(dq);
	normalized.print("normalized Euclidean line");

	dq.set(0, 0, 0, 0, 5, 6, 7, 8);
	dq.print("whole dual quaternion (Ideal)");
	normalized = DQMath::normalize(dq);
	normalized.print("normalized Ideal line");
}

void quadAreaTest() {
	const string name = " quadAreaTest";
	float epsilon = VERY_SMALL * 1;

	// Scott asks, what if the quad looks like a triangle?
	Vec3 v0(0, 0, 0);
	Vec3 v1(0, 0.5, 0);
	Vec3 v2(0, 1, 0);
	Vec3 v3(-1, 0, 0);
	// Area should be 0.5
	const float correctAnswer = 0.5;
	Quad quad = Quad(v0, v1, v2, v3);
	float area = QuadMath::getArea(quad);

	bool flag = (area - correctAnswer) < epsilon;
	printPassedOrFailed(flag, name);

	//{
	//	// This should blow up as it has an area of zero
	//	Vec3 v0(0, 0, 0);
	//	Vec3 v1(0, 0.5, 0);
	//	Vec3 v2(0, 1, 0);
	//	Vec3 v3(0, 2, 0);
	//	Quad quad = Quad(v0, v1, v2, v3);
	//}
}

// VISUALIZED: https://github.com/ScottFielder/MathLibrary/blob/master/Images/closestPointOnQuadTest.png
void closestPointOnQuadTest() {
	const string name = " closestPointOnQuadTest";
	float epsilon = VERY_SMALL * 1;
	float diffMag;

	Vec3 pos1(-1, 0.5, 0);
	Vec3 pos2(0, 0.35, 2.5);
	Vec3 pos3(1, 1, 0);
	Vec3 pos4(2, 0.01, -3);
	// Wind the quad anti-clockwise
	Vec3 v0 = Vec3(0, 0, 0);
	Vec3 v1 = Vec3(1, 0, 0);
	Vec3 v2 = Vec3(0.5, 1, 0);
	Vec3 v3 = Vec3(0, 1, 0);
	Quad quad = Quad(v0, v1, v2, v3);

	Vec3 closestPoint1, closestPoint2, closestPoint3, closestPoint4;
	Vec3 correctAnswer1, correctAnswer2, correctAnswer3, correctAnswer4;
	closestPoint1 = QuadMath::closestPointOnQuad(pos1, quad);
	// Looking at the graph, answer should be:
	correctAnswer1.set(0, 0.5, 0);

	closestPoint2 = QuadMath::closestPointOnQuad(pos2, quad);
	// Looking at the graph, answer should be:
	correctAnswer2.set(0, 0.35, 0);

	closestPoint3 = QuadMath::closestPointOnQuad(pos3, quad);
	// Looking at the graph, answer should be:
	correctAnswer3.set(0.6, 0.8, 0);

	closestPoint4 = QuadMath::closestPointOnQuad(pos4, quad);
	// Looking at the graph, answer should be:
	correctAnswer4 = v1;

	bool test1 = false;
	diffMag = VMath::mag(correctAnswer1 - closestPoint1);
	if (diffMag < epsilon) {
		test1 = true;
	}

	bool test2 = false;
	diffMag = VMath::mag(correctAnswer2 - closestPoint2);
	if (diffMag < epsilon) {
		test2 = true;
	}

	bool test3 = false;
	diffMag = VMath::mag(correctAnswer3 - closestPoint3);
	if (diffMag < epsilon) {
		test3 = true;
	}

	bool test4 = false;
	diffMag = VMath::mag(correctAnswer4 - closestPoint4);
	if (diffMag < epsilon) {
		test4 = true;
	}

	bool flag = test1 && test2 && test3 && test4;
	printPassedOrFailed(flag, name);
}

// VISUALIZED: https://github.com/ScottFielder/MathLibrary/blob/master/Images/pointInsideQuad.png
void pointInsideQuadTest() {
	const string name = " pointInsideQuadTest";

	Vec4 point1(0, 0, 0, 1);
	Vec4 point2(2, 0, 0, 1);
	Vec4 point3(0, 0.5, 0, 1);
	Vec4 point4(1, 1, 0, 1);
	Vec4 point5(1.05, 1.05, 0, 1);

	// This quad is a unit square
	Quad quad = Quad(
		Vec3(0, 0, 0),
		Vec3(1, 0, 0),
		Vec3(1, 1, 0),
		Vec3(0, 1, 0)
	);

	// Looking at graph, we know points 1, 3, 4 are in quad
	bool test1 = false;
	bool test2 = false;
	bool test3 = false;
	bool test4 = false;
	bool test5 = false;

	if (QuadMath::isPointInside(point1, quad)) {
		test1 = true;
	}

	if (QuadMath::isPointInside(point2, quad) == false) {
		test2 = true;
	}

	if (QuadMath::isPointInside(point3, quad)) {
		test3 = true;
	}

	if (QuadMath::isPointInside(point4, quad)) {
		test4 = true;
	}

	if (QuadMath::isPointInside(point5, quad) == false) {
		test5 = true;
	}

	bool flag = test1 && test2 && test3 && test4 && test5;
	printPassedOrFailed(flag, name);
}


void triangleTest() {
	const string name = " triangleTest";
	const float epsilon = VERY_SMALL * 1;

	// Line below shld throw if you uncomment it
	// Triangle t(Vec3(0, 0, 0), Vec3(1, 0, 0), Vec3(2, 0, 0));

	Triangle tri1(Vec3(0, 0, 0), Vec3(0, 1, 0), Vec3(1, 0, 0));

	Plane p_using_getPlane = TMath::getPlane(tri1);
	Plane p(Vec3(0, 0, 0), Vec3(0, 1, 0), Vec3(1, 0, 0));

	bool test0 = false;
	Plane pDiff = p - p_using_getPlane;
	if (fabs(pDiff.x) < epsilon && fabs(pDiff.y) < epsilon && fabs(pDiff.z) < epsilon && fabs(pDiff.d) < epsilon) {
		test0 = true;
	}

	// This should be in the triangle
	Vec3 p1(0, 0, 0);
	// This should be outside
	Vec3 p2(1, 1, 0);
	// This should be outside too
	Vec3 p3(0, 1.0001, 0);

	bool test1 = false;
	bool test2 = false;
	bool test3 = false;

	if (TMath::isPointInside(p1, tri1)) {
		test1 = true;
	}

	if (TMath::isPointInside(p2, tri1) == false) {
		test2 = true;
	}

	if (TMath::isPointInside(p3, tri1) == false) {
		test3 = true;
	}

	bool flag = test0 && test1 && test2 && test3;
	printPassedOrFailed(flag, name);
}

void rayTest() {
	Vec3 v1(0.0f, 0.0f, 0.0f);
	Vec3 v2(1.0f, 0.0f, 0.0f);
	Ray ray(v1, v2);
	Vec3 v3 = ray.getPos(0.5f);
	v3.print();
	Plane plane(0.0f, 1.0f, 0.0f, 10.0f);
	//Vec3 intersection = RMath::rayPlaneIntersection(ray,plane);
	//intersection.print();
}
