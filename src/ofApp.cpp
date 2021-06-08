#include "ofApp.h"

//--------------------------------------------------------------

vector<string> split(string str, string separator) {
	if (separator == "") return { str };
	vector<string> result;
	string tstr = str + separator;
	long l = tstr.length(), sl = separator.length();
	string::size_type pos = 0, prev = 0;

	for (; pos < l && (pos = tstr.find(separator, pos)) != string::npos; prev = (pos += sl)) {
		result.emplace_back(tstr, prev, pos - prev);
	}
	return result;
}

void ofApp::setup() {
	ofSetBackgroundColor(0);
	mesh.setMode(OF_PRIMITIVE_POINTS);

	char buf[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, buf);
	cout << buf << endl;

	//example
	string filepath = "data/1a04e3eab45ca15dd86060f189eb133.pts";

	//interactive 
	//string filepath;
	//cout << "input filepath = ";
	//cin >> filepath;
	//cout << "inputFile : " << filepath << "\n";


	std::ifstream ifs(filepath);

	const int buf_size = 81;

	char str[buf_size];
	if (ifs.fail()) {
		std::cerr << "Failed to open file." << std::endl;
	}
	while (ifs.getline(str, buf_size)) {
		std::cout << str << std::endl;
		vector<string> pos = split(str, " ");
		ofVec3f p = ofVec3f(std::stof(pos[0]), std::stof(pos[1]), std::stof(pos[2]));
		positions.push_back(p);
		mesh.addVertex(p * 100.0);
	}

	cout << "point num : " << mesh.getVertices().size() << endl;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofEnableDepthTest();
	cam.begin();
	mesh.draw();
	cam.end();
	ofDisableDepthTest();
}