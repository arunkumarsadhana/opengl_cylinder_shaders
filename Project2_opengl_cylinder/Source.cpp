
#include "Shader.h"
#define M_PI 3.14159265
int WIDTH;
int HEIGHT;
int width;
int height;
float r;
float theta;
GLuint deltaTime,time;
GLuint vboHandle[1];
GLuint indexVBO;
GLFWwindow* window;
GLuint VAO,VBO,VAO1,VBO1;
GLuint shaderProgram,shaderProgram1;
float angle=0.0f;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
/*struct vertex{
   GLfloat x,z, y_start, y_end;
}each_pole; // struct
*/
struct vertex{
   GLfloat x,y,z,s,t,u;
}each_pole;

std::vector<vertex> each_pole_vector; // vector of structs
struct cylin{
	GLfloat x,y,z;
}center;
std::vector<GLuint> indeces;
static GLfloat vertices[] = {
		-2.0, -2.0, -1.0,// Left  
		2.0,-2.0,-1.0,// Right 
		2.0,2.0,-1.0,// Top   
		-2.0,2.0,-1.0
    };
void do_movement();
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
glm::vec3 cameraside = glm::vec3(1.0f, 0.0f, 0.0f);
bool keys[1024];

void initNormal(){
//Cylinder with y axis up
/*GLfloat cylinder_height = 1.0f,
        cylinder_radius = 0.5f,
        nr_of_points_cylinder = 360.0f;
		center.x=0.0;
		center.y=0.0;
		center.z=0.05;
for (int i = 0; i < nr_of_points_cylinder; ++i)
{
    GLfloat u = i / (GLfloat)nr_of_points_cylinder;

    //Where the cylinder is in the x and z positions (3D space) 
    each_pole.x = center.x + cylinder_radius*cos(2*(22.0/7.0)*u); 
    each_pole.z = center.z + cylinder_radius*sin(2*(22.0/7.0)*u); 

    each_pole.y_start = 0.0f;
    each_pole.y_end = cylinder_height;

    each_pole_vector.push_back(each_pole);
	indeces.push_back(i);
}*/
	
	
		int numMajor = 6;
		int numMinor = 16;
		float height = 1.0;
		float radius = 0.4;
	double majorStep = height / numMajor;
double minorStep = 2.0 * M_PI / numMinor;
int i, j;
for (i = 0; i < numMajor; ++i) {
GLfloat z0 = 0.5 * height - i * majorStep;
GLfloat z1 = z0 - majorStep;
for (j = 0; j <= numMinor; ++j) {
double a = j * minorStep;
GLfloat x = radius * cos(a);
GLfloat y = radius * sin(a);
glNormal3f(x / radius, y / radius, 0.0);
each_pole.x=x;
each_pole.y=y;
each_pole.z=z0;
glNormal3f(x / radius, y / radius, 0.0);
each_pole.s=x;
each_pole.t=y;
each_pole.u=z1;
 each_pole_vector.push_back(each_pole);
	indeces.push_back(j);
}
}
}
//float i=0.0f;






int main(int argc, char** argv){
       std::cout << "entered";
    
    WIDTH = 1000;
    HEIGHT = 1000;
    glfwInit();
    // Set all the required options for GLFW
    
	initNormal();

	//cout<<"vector size="<<each_pole_vector.size()<<endl;

    // Create a GLFWwindow object that we can use for GLFW's functions
    window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();
  glfwGetFramebufferSize(window, &width, &height);
   glViewport(0, 0, width, height);
    glfwSetKeyCallback(window, key_callback);
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
	 GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
	 shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

	/*GLuint vertexShader1 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader1, 1, &vertexShaderSource1, NULL);
    glCompileShader(vertexShader1);
	 GLuint fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader1);
	 shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader1);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);
	 glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
	 glDeleteShader(vertexShader1);
    glDeleteShader(fragmentShader1);
	*/
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1,&VBO);
    glGenBuffers(1, &indexVBO);
	//glGenVertexArrays(1,&VAO1);
	//glGenBuffers(1,&VBO1);
	//glBindVertexArray(VAO1);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_DYNAMIC_DRAW);
	//glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(vertices),(GLvoid*)0);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	//glEnableVertexAttribArray(0);
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex)* each_pole_vector.size(), &each_pole_vector[0], GL_DYNAMIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indeces.size(), &indeces[0], GL_STATIC_DRAW);

	
	
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(vertex), (GLvoid*)0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,8*sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	glBindVertexArray(0);
	
    //glutReshapeFunc(reshape);
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
		 do_movement();
		
        // Render
        // Clear the colorbuffer
		glClearColor(0.1, 0.1, 0.1, 1.0);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glColor4f(1, 1, 1, 1);
	  // glUseProgram(shaderProgram1);
	   // glBindVertexArray(VAO1);
		//glDrawArrays(GL_QUADS, 0, 4);
        //glBindVertexArray(0);
	glUseProgram(shaderProgram);

	

        glBindVertexArray(VAO);
        
		 glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        // Projection 
        glm::mat4 projection;
        projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
        GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
		for (GLuint i = 0; i < indeces.size(); i++)
        {
            // Calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model;
			model = glm::translate(model, glm::vec3(0.0,0.0,0.1));
            GLfloat angle = 3.6f * i;
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			//model = glm::rotate(model, angle, glm::vec3(each_pole_vector[i].x,each_pole_vector[i].y,each_pole_vector[i].z));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

             glDrawElements(GL_TRIANGLE_STRIP, indeces.size(), GL_UNSIGNED_INT, (char*)NULL + 0);
        
       
        }
        glBindVertexArray(0);



          


	/*glBindVertexArray(VAO);
	 for(GLuint i = 0; i < 10; i++)
        {
            // Calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 transform;
            //transform = glm::translate(transform, glm::vec3(0.5f, -0.3f, 0.0f));
            GLfloat angle = 20.0f * i; 
            transform = glm::rotate(transform, (GLfloat)glfwGetTime()*angle, glm::vec3(0.0f, 0.0f, 1.0f));
			//cout<<"angle="<<angle<<endl;
			GLint transformLoc = glGetUniformLocation(shaderProgram, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));   
			glDrawElements(GL_TRIANGLE_STRIP, indeces.size(), GL_UNSIGNED_INT, (char*)NULL + 0);
        }	
		
	//glDrawElements(GL_TRIANGLES, indeces.size(), GL_UNSIGNED_INT, (char*)NULL + 0);//2 indeces needed to make one line 
	//glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, (char*)NULL + 0);//2 indeces needed to make one line 
	//glDrawElements(GL_TRIANGLE_STRIP, indeces.size(), GL_UNSIGNED_INT, (char*)NULL + 0);

	
	glBindVertexArray(0);*/
		glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &indexVBO);
	glDeleteBuffers(1,&VBO);
	//glDeleteBuffers(1, &colorbuffer);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;

}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void do_movement()
{
    // Camera controls
    GLfloat cameraSpeed = 0.001f;
    if (keys[GLFW_KEY_W])
        cameraPos += cameraSpeed * cameraFront;
    if (keys[GLFW_KEY_S])
        cameraPos -= cameraSpeed * cameraFront;
    if (keys[GLFW_KEY_A])
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (keys[GLFW_KEY_D])
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if(keys[GLFW_KEY_Q])
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraside)) * cameraSpeed;
	if(keys[GLFW_KEY_E])
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraside)) * cameraSpeed;
}