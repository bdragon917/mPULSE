#include <RenderingEngine/Shader.h>
#include <fstream>

Shader::Shader(const char *fs, const char *vs) {
	char *vsf = NULL;
	char *fsf = NULL;
	vsf = textFileRead(vs); // Load the vertex shader
	fsf = textFileRead(fs); // Load the fragment shader
	const char *ff = fsf;
	const char *vv = vsf;

	if (vsf != NULL && fsf != NULL) { // If the files were loaded successfully, create the shader objects
		v = glCreateShader(GL_VERTEX_SHADER);
		f = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(v, 1, &vv, NULL);
		glShaderSource(f, 1, &ff, NULL);
		glCompileShader(v); // Compile the shader files
		glCompileShader(f);
		p = glCreateProgram();
		glAttachShader(p, v); // Put everything together
		glAttachShader(p, f);
		glLinkProgram(p);
		glUseProgram(p);

		int infologLength = 0;
		int charsWritten  = 0;
		char *infoLog;

		glGetProgramiv(p, GL_INFO_LOG_LENGTH, &infologLength); // Print any errors reported by the shader during compilation 
		if (infologLength > 0) {
			infoLog = (char *)malloc(infologLength);
			glGetProgramInfoLog(p, infologLength, &charsWritten, infoLog);
			printf("%s\n",infoLog);
			cout << infoLog;
			free(infoLog);
		}
	}
	if (vsf == NULL) { // Errors if the shader files were not found
		cout << "Cannot find shader file " << vs;
	}
	if (fsf == NULL) {
		cout << "Cannot find shader file " << fs;
	}
}

void Shader::on() {
	glUseProgram(p);
}

void Shader::off() {
	glUseProgram(NULL);
}

// Code below modified from code originally written by Wojtek Palubicki
char *Shader::textFileRead(const char* filename) {
	char *content = NULL;
	if (filename != NULL) {
        // Opens file as input, binary, and with read pointer at end
        cout << "Reading " << filename << endl;
        fstream file (filename, ios_base::in | ios_base::binary | ios_base::ate);

		if (file.is_open()) {
            // Determines filesize then resets read location to beginning
            unsigned filesize = static_cast<unsigned>(file.tellg());
            file.seekg(0);

            // Reads contents of file into array
			if (filesize > 0) {
                content = new char[filesize+1];
                file.read(content, filesize);
                content[filesize] = '\0';
			}

			file.close();
		}
	}
	return content;
}

int Shader::textFileWrite(char *fn, char *s) {
	
	printf("WTF!!!/n");
	/**
	FILE *fp;
	int status = 0;

	if (fn != NULL) {
		fp = fopen(fn,"w");

		if (fp != NULL) {

			if (fwrite(s,sizeof(char),strlen(s),fp) == strlen(s))
				status = 1;
			fclose(fp);
		}
	}
	return(status);
	**/
	return 1; //=)
}

// Returns the location of the given shader uniform, or an error if it was not found
int Shader::getUniLoc(const char *name) {
	int loc;
	loc = glGetUniformLocation(p, name);

	if (loc == -1)
		cout << "No such uniform named" << name;

	return loc;
}


// Returns the location of the given shader attribute, or an error if it was not found
int Shader::getAttrLoc(const char *name) {
	int loc;
	loc = glGetAttribLocation(p, name);

	if (loc == -1)
		cout << "No such attribute named" << name;

	return loc;
}
