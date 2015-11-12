# OpenGL Framework
This framework simplifies the setup process and manages basic OpenGL Objects. However, it some naive assumptions that may not fit all purposes. I sought to write a general-purpose framework at the level of OpenGL I know, which is very little.

Each of the classes are relatively simple, and is intuitively named:

## *App
### Manages the overall application

Example :
> App myApp(argc,argv);
> myApp.setInit(init); //setup function
> myApp.setDisplay(display); //drawing function
> myApp.run(); //continuous loop

## *GLObject
### Manages an object (i.e. what to be drawn)

Example :
> //initializing an object
> GLObject* Cube = new GLObject();
> Cube->push(vertexPositions);
> Cube->push(vertexColors);
> Cube->push(vertexIndices);
> //drawing an object
> Cube->apply();
> Cube->draw();

## *GLAttrib
### Manages vertex attributes

Example :
> GLAttrib* vertexPositions = new GLAttrib(vPosData,size,elemSize,AttribLocation);

## *GLBuffer
### Manages general-purpose buffers

Example :
> // binds to GL_ELEMENT_ARRAY_BUFFER
> GLBuffer* vertexIndices = new GLBuffer(vIndData,GL_ELEMENT_ARRAY_BUFFER,size,typeSize,elemSize);

## *GLShader
### Thin Wrapper to shader

Example :
> GLShader v(GL_VERTEX_SHADER,"vShader.txt")
> //or alternatively with a full source string

## *GLProgram
### Thin Wrapper to shaderProgram

Example :
> //initialize
> GLProgram* shaderProgram = new GLProgram(shaderList);
> //use
> glUseProgram(*shaderProgram);
