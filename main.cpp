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
		camX += dirX * speed;
		camZ += dirZ * speed;
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		camX -= dirX * speed;
		camZ -= dirZ * speed;
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		camX -= dirZ * speed;
		camZ += dirX * speed;
	}
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		camX += dirZ * speed;
		camZ -= dirX * speed;
	}

	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
		camY += speed;
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
		camY -= speed;
	}
}



void lookAt(float eyeX, float eyeY, float eyeZ,
            float centerX, float centerY, float centerZ,
            float upX, float upY, float upZ)
{
    float fX = centerX - eyeX;
    float fY = centerY - eyeY;
    float fZ = centerZ - eyeZ;

    // normaliza forward
    float fLen = sqrt(fX*fX + fY*fY + fZ*fZ);
    fX /= fLen; fY /= fLen; fZ /= fLen;

    // normaliza up
    float upLen = sqrt(upX*upX + upY*upY + upZ*upZ);
    upX /= upLen; upY /= upLen; upZ /= upLen;

    // right = forward × up
    float rX = fY * upZ - fZ * upY;
    float rY = fZ * upX - fX * upZ;
    float rZ = fX * upY - fY * upX;

    // new up = right × forward
    float uX = rY * fZ - rZ * fY;
    float uY = rZ * fX - rX * fZ;
    float uZ = rX * fY - rY * fX;

    float m[16] = {
        rX,  uX, -fX, 0,
        rY,  uY, -fY, 0,
        rZ,  uZ, -fZ, 0,
        0,   0,   0,  1
    };

    glMultMatrixf(m);
    glTranslatef(-eyeX, -eyeY, -eyeZ);
}




int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Janela", glfwGetPrimaryMonitor(), NULL);
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
		
		dirX = cosf(radYaw) * cosf(radPitch);
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
		lookAt(camX, camY, camZ,
       camX + dirX, camY + dirY, camZ + dirZ,
       0, 1, 0);

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