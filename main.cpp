#include <GLFW/glfw3.h>
#include <cmath>

float dirX, dirY, dirZ;
float camX = 0.f, camY = 0.f, camZ = 0.f;
float yaw = 0.f;
float pitch = 0.0f;
float lastX = 400, lastY = 300;
bool firstMouse = true;
float speed = 0.1f;

void processInput(GLFWwindow* window, float radYaw, float radPitch){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		camX += -sin(radYaw) * speed;
		camZ += -cosf(radYaw) * speed;
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		camX -= -sinf(radYaw) * speed;
		camZ -= -cosf(radYaw) * speed;
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		camX += cosf(radYaw) * speed;
		camZ += -sinf(radYaw) * speed;
	}
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		camX -= cosf(radYaw) * speed;
		camZ -= -sinf(radYaw) * speed;
	}

	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
		camY += speed;
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
		camY -= speed;
	}
}




int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 450, "Janela", NULL, NULL);
	glfwMakeContextCurrent(window);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glClearColor(0.4f, 0.3f, 0.76f, 1.0f);
	
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		
		if(firstMouse){
			lastX = mouseX;
			lastY = mouseY;
			firstMouse = false;
		}

		float xoffset = mouseX - lastX;
		float yoffset = lastY - mouseY;
		lastX = mouseX;
		lastY = mouseY;

		float sensitivity = 0.05f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.f) pitch = 89.f;
		if (pitch < -89.f) pitch = -89.f;

		float radYaw = yaw * 3.14159f / 180.f;
		float radPitch = pitch * 3.14159f / 180.f;
		
		dirX = cosf(radPitch) * cosf(radYaw);
		dirY = sinf(radPitch);
		dirZ = sinf(radYaw) * cosf(radPitch);

		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		processInput(window, radYaw, radPitch);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1, 1, -0.75, 0.75, 1, 100);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(-yaw, 0, 1, 0);
		glRotatef(-pitch, 1, 0, 0);
		glTranslatef(-camX, -camY, -camZ);

		glPushMatrix();
		glTranslatef(-3.f, 1, -5);
		

		glBegin(GL_QUADS);

			//frente
			glColor3f(0.3f, 0.1f, 0.75f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			
			//tras
			glColor3f(0.54f, 0.2f, 0.98f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			
			//esquerda
			glColor3f(0.1f, 0.3f, 0.87f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			
			//direita
			glColor3f(0.33f, 0.12f, 0.76f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			
			//topo
			glColor3f(0.66f, 0.44f, 0.76f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			
			//base
			glColor3f(1.0f, 0.3f, 0.8f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
		glEnd();
		glPopMatrix();

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}