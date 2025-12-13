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

void createCube(float tamanho, float cores[18]){
	glBegin(GL_QUADS);
		float x = 0, y = 0, z = 0;
		glColor3f(cores[0], cores[1], cores[2]);
		glVertex3f(x, y, z);
		glVertex3f(x-tamanho, y, z);
		glVertex3f(x-tamanho, y-tamanho, z);
		glVertex3f(x, y-tamanho, z);
		glColor3f(cores[3], cores[4], cores[5]);
		glVertex3f(x, y, z-tamanho);
		glVertex3f(x-tamanho, y, z-tamanho);
		glVertex3f(x-tamanho, y-tamanho, z-tamanho);
		glVertex3f(x, y-tamanho, z-tamanho);
		glColor3f(cores[6], cores[7], cores[8]);
		glVertex3f(x-tamanho, y, z);
		glVertex3f(x-tamanho, y, z-tamanho);
		glVertex3f(x-tamanho, y-tamanho, z-tamanho);
		glVertex3f(x-tamanho, y-tamanho, z);
		glColor3f(cores[9], cores[10], cores[11]);
		glVertex3f(x, y, z);
		glVertex3f(x, y, z-tamanho);
		glVertex3f(x, y-tamanho, z-tamanho);
		glVertex3f(x, y-tamanho, z);
		glColor3f(cores[12], cores[13], cores[14]);
		glVertex3f(x, y, z);
		glVertex3f(x, y, z-tamanho);
		glVertex3f(x-tamanho, y, z-tamanho);
		glVertex3f(x-tamanho, y, z);
		glColor3f(cores[15], cores[16], cores[17]);
		glVertex3f(x, y-tamanho, z);
		glVertex3f(x, y-tamanho, z-tamanho);
		glVertex3f(x-tamanho, y-tamanho, z-tamanho);
		glVertex3f(x-tamanho, y-tamanho, z);

	glEnd();
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
	GLFWwindow* window = glfwCreateWindow(1024, 600, "Janela", glfwGetPrimaryMonitor(), NULL);
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
		
		float cores[18] = {
			0.3f, 0.2f, 0.65f,
			0.43f, 0.32f, 0.87f,
			0.45f, 0.77f, 0.32f,
			0.32f, 0.87f, 0.2f,
			0.87f, 0.45f, 0.32f,
			0.45f, 0.12f, 0.87f
	
		};

		glPushMatrix();
		glTranslatef(-3.f, 1, 7);
		createCube(4, cores);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-7, 1, 10);
		createCube(6, cores);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(-3, 1, -5);
		createCube(5, cores);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(12, 1, -8);
		createCube(5, cores);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-20, 5, -20);
		glBegin(GL_TRIANGLES);
			glColor3f(0.3f, 0.65f, 0.87f);
			glVertex3f(0, 0, 0);
			glVertex3f(-4, 0, 0);
			glVertex3f(-2, 5, -3);

			glColor3f(0.45f, 0.12f, 0.98f);
			glVertex3f(0, 0, 0);
			glVertex3f(-2, 0, -6);
			glVertex3f(-2, 5, -3);

			glColor3f(0.12f, 0.45f, 0.38f);
			glVertex3f(-2, 0, -6);
			glVertex3f(-4, 0, 0);
			glVertex3f(-2, 5, -3);

			glColor3f(0.6f, 0.87f, 0.32f);
			glVertex3f(-4, 0, 0);
			glVertex3f(-2, 0, -6);
			glVertex3f(0, 0, 0);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(30, 5, 10);
		createCube(10, cores);
		glPopMatrix();

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}