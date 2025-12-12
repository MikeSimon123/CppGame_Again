#include <GLFW/glfw3.h>

float x = 0, z = 0, y = 0;
float speed = 0.05f;

void processInput(GLFWwindow* window){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		z += speed;
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		z -= speed;
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		x -= speed;
	}
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		x += speed;
	}
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
		y -= speed;
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
		y += speed;
	}
}

void createCube(float tamanho){
	float x = 0, y = 0, z = 0;
	glBegin(GL_QUADS);
		glColor3f(0.3f, 0.67f, 0.32f);
		glVertex3f(x, y, z);
		glVertex3f(x - tamanho, y, z);
		glVertex3f(x - tamanho, y - tamanho, z);
		glVertex3f(x, y - tamanho, z);

		glColor3f(0.45f, 0.32f, 0.12f);
		glVertex3f(x, y, z - tamanho);
		glVertex3f(x - tamanho, y, z - tamanho);
		glVertex3f(x - tamanho, y - tamanho, z - tamanho);
		glVertex3f(x, y - tamanho, z - tamanho);

		glColor3f(0.41f, 0.78f, 0.98f);
		glVertex3f(x - tamanho, y, z);
		glVertex3f(x - tamanho, y, z - tamanho);
		glVertex3f(x - tamanho, y - tamanho, z - tamanho);
		glVertex3f(x - tamanho, y - tamanho, z);

		glColor3f(0.65f, 0.21f, 0.87f);
		glVertex3f(x, y, z);
		glVertex3f(x, y, z - tamanho);
		glVertex3f(x, y - tamanho, z - tamanho);
		glVertex3f(x, y - tamanho, z);

		glColor3f(0.32f, 0.97f, 0.4f);
		glVertex3f(x, y, z);
		glVertex3f(x, y, z - tamanho);
		glVertex3f(x - tamanho, y, z - tamanho);
		glVertex3f(x - tamanho, y, z);

		glColor3f(0.12f, 0.45f, 0.3f);
		glVertex3f(x, y - tamanho, z);
		glVertex3f(x - tamanho, y - tamanho, z);
		glVertex3f(x - tamanho, y - tamanho, z - tamanho);
		glVertex3f(x, y - tamanho, z - tamanho);
	glEnd();
}

int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(1024, 600, "Janela", glfwGetPrimaryMonitor(), NULL);
	glfwMakeContextCurrent(window);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.55f, 0.14f, 0.87f, 1.0f);

	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		processInput(window);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1, 1, -0.75, 0.75, 1, 100);
	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(-2 + x, 0 + y, -5 + z);
		createCube(3);

		glLoadIdentity();
		glTranslatef(2 + x, 0 + y, -4 + z);
		glRotatef(25.f, 0, 0.45, 0);
		createCube(2);

		glLoadIdentity();
		glTranslatef(2.f + x, 0 + y, -10.f + z);
		glRotatef(30.f, 0.45, 0, 0);
		createCube(5);

		

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}