# OpenGL Framework
This framework simplifies the setup process and manages basic OpenGL Objects. However, it some naive assumptions that may not fit all purposes. I sought to write a general-purpose framework at the level of OpenGL I know, which is very little.

Each of the classes are relatively simple, and is intuitively named:

## *App
### Manages the overall application

Example :

``` c++
class myApp:public App{
	public:
	myApp():App(){};

	//if command line arguments are desirable
	//myApp(int argc, char** argv):App(argc,argv){};

	void display(){
		//drawing body
	}
	
	void init(){
		//initializing body
	};
};

//Usage
int main(int argc, char** argv){
	//if command line arguments are desirable
	//myApp drawCube(argc,argv); 

	myApp drawCube();
	drawCube.init();
	drawCube.run();
	return 0;
}
```

## *GLObject
### Manages an object (i.e. what to be drawn)

Example :

``` c++
 //initializing an object
 GLObject* Cube = new GLObject();
 Cube->push(vertexPositions);
 Cube->push(vertexColors);
 Cube->push(vertexIndices);
 //drawing an object
 Cube->apply();
 Cube->draw();
```

## *GLAttrib
### Manages vertex attributes

Example :

``` c++
 GLAttrib* vertexPositions = new GLAttrib(vPosData,size,elemSize,AttribLocation);
```

## *GLBuffer
### Manages general-purpose buffers

Example :

``` c++
 // binds to GL_ELEMENT_ARRAY_BUFFER
 GLBuffer* vertexIndices = new GLBuffer(vIndData,GL_ELEMENT_ARRAY_BUFFER,size,typeSize,elemSize);
```

## *GLShader
### Thin Wrapper to shader

Example :

``` c++
 GLShader v(GL_VERTEX_SHADER,"vShader.txt")
 //or alternatively with a full source string
```

## *GLProgram
### Thin Wrapper to shaderProgram

Example :

``` c++
 //initialize
 GLProgram* shaderProgram = new GLProgram(shaderList);
 //use
 glUseProgram(*shaderProgram);
```
# Next Steps
* Add Scene
	* Separate Viewports
	* Contain Objects
* Add Camera
* Add Interactivity
	* Mouse
		* Rotate View
		* Object Selection
	* Keyboard
		* Mobilitiy
		* Other Commands
* Add Texture
* Add Instantiation
* Add Lights
	* Specular
	* Point
	* Directional

