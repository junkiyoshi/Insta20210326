#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	ofColor color;
	vector<int> hex_list = { 0xef476f, 0xffd166, 0x06d6a0, 0x118ab2, 0x073b4c };
	vector<ofColor> base_color_list;
	for (auto hex : hex_list) {

		color.setHex(hex);
		base_color_list.push_back(color);
	}

	int span = 20;
	for (int x = -220; x <= 220; x += span) {

		for (int y = -220; y <= 220; y += span) {

			for (int z = -220; z <= 220; z += 440) {

				this->location_list.push_back(glm::vec3(x, y, z));
				this->color_list.push_back(base_color_list[(int)ofRandom(base_color_list.size())]);
			}
		}
	}

	for (int x = -220; x <= 220; x += 440) {

		for (int y = -220; y <= 220; y += span) {

			for (int z = -220 + span; z <= 220 - span; z += span) {

				this->location_list.push_back(glm::vec3(x, y, z));
				this->color_list.push_back(base_color_list[(int)ofRandom(base_color_list.size())]);
			}
		}
	}

	for (int x = -220 + span; x <= 220 - span; x += span) {

		for (int y = -220; y <= 220; y += 440) {

			for (int z = -220 + span; z <= 220 - span; z += span) {

				this->location_list.push_back(glm::vec3(x, y, z));
				this->color_list.push_back(base_color_list[(int)ofRandom(base_color_list.size())]);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->frame.clear();

	float size;
	for (int i = 0; i < this->location_list.size(); i++) {

		auto noise_value = ofNoise(glm::vec4(this->location_list[i] * 0.005, ofGetFrameNum() * 0.01));
		if (noise_value < 0.5) { size = 0; }
		else if (noise_value > 0.55) { size = 20; }
		else { size = ofMap(noise_value, 0.5, 0.55, 0, 20); }

		this->setBoxToMesh(this->face, this->frame, this->location_list[i], size, this->color_list[i]);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.21);
	ofRotateY(ofGetFrameNum() * 0.37);

	this->face.draw();

	ofSetColor(39);
	this->frame.drawWireframe();

	ofNoFill();
	ofSetColor(39);
	ofDrawBox(440 + 16);

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float size, ofColor face_color) {

	this->setBoxToMesh(face_target, frame_target, location, size, size, size, face_color);
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float height, float width, float depth, ofColor face_color) {

	int face_index = face_target.getNumVertices();
	int frame_index = frame_target.getNumVertices();

	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * 0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * 0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * 0.5 * 0.99, depth * 0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * 0.5 * 0.99, depth * 0.5 * 0.99));

	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * -0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * -0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * -0.5 * 0.99, depth * 0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * -0.5 * 0.99, depth * 0.5 * 0.99));

	face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 2);
	face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 3);

	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 6);
	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 7);

	face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 1);
	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 1);

	face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 6);
	face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 1);

	face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 7);
	face_target.addIndex(face_index + 7); face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 2);

	face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 7); face_target.addIndex(face_index + 4);
	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 3);

	frame_target.addVertex(location + glm::vec3(width * -0.5, height * 0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * 0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * 0.5, depth * 0.5));
	frame_target.addVertex(location + glm::vec3(width * -0.5, height * 0.5, depth * 0.5));

	frame_target.addVertex(location + glm::vec3(width * -0.5, height * -0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * -0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * -0.5, depth * 0.5));
	frame_target.addVertex(location + glm::vec3(width * -0.5, height * -0.5, depth * 0.5));

	frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 1);
	frame_target.addIndex(frame_index + 1); frame_target.addIndex(frame_index + 2);
	frame_target.addIndex(frame_index + 2); frame_target.addIndex(frame_index + 3);
	frame_target.addIndex(frame_index + 3); frame_target.addIndex(frame_index + 0);

	frame_target.addIndex(frame_index + 4); frame_target.addIndex(frame_index + 5);
	frame_target.addIndex(frame_index + 5); frame_target.addIndex(frame_index + 6);
	frame_target.addIndex(frame_index + 6); frame_target.addIndex(frame_index + 7);
	frame_target.addIndex(frame_index + 7); frame_target.addIndex(frame_index + 4);

	frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 4);
	frame_target.addIndex(frame_index + 1); frame_target.addIndex(frame_index + 5);
	frame_target.addIndex(frame_index + 2); frame_target.addIndex(frame_index + 6);
	frame_target.addIndex(frame_index + 3); frame_target.addIndex(frame_index + 7);

	for (int i = 0; i < 8; i++) {

		face_target.addColor(face_color);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}