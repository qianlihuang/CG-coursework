// Shapes.c
// OpenGL SuperBible, Chapter 3
// Demonstrates GLUT menuing and some GLUT prebuilt shapes
// Program by Richard S. Wright Jr.

// Modified by Yiliu Dong
// Modifications:
// 1. Allow control of light position using WASD keys
// 2. Add custom light


#include <windows.h>
#include <glut.h>

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

// Light values and coordinates
GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPos[] = { 0.0f, 0.0f, 2.0f, 1.0f }; // Initial light position

static int iShape = 1; // Shape code
static int iLight = 0; // Light code

GLuint texture; // Texture object
int textureEnabled = 0; // Flag to toggle texture on/off

///////////////////////////////////////////////////////////////////////////////

// Function to generate a simple checkerboard texture
void GenerateTexture() {
    unsigned char textureData[64 * 64 * 3]; // 64x64 checkerboard texture (RGB)
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            int c = ((i + j) % 2) * 255;  // Alternating colors (white/black)
            textureData[(i * 64 + j) * 3 + 0] = c;  // Red
            textureData[(i * 64 + j) * 3 + 1] = c;  // Green
            textureData[(i * 64 + j) * 3 + 2] = c;  // Blue
        }
    }

    glGenTextures(1, &texture);  // Generate texture ID
    glBindTexture(GL_TEXTURE_2D, texture);  // Bind the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);  // Load texture data

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

// Function to enable/disable texture
void ToggleTexture(int value) {
    textureEnabled = value;  // Set texture enable/disable flag
    glutPostRedisplay();  // Redraw the scene
}

// Function to generate random floats between a given range
float RandomFloat(float min, float max) {
    return min + (float)rand() / (float)(RAND_MAX / (max - min));
}

// Function to set random parameters for light 1
void SetRandomLight1() {
    GLfloat ambientLight1[] = {
        RandomFloat(0.0f, 1.0f), 
        RandomFloat(0.0f, 1.0f), 
        RandomFloat(0.0f, 1.0f), 
        1.0f 
    };
    
    GLfloat diffuseLight1[] = {
        RandomFloat(0.0f, 1.0f), 
        RandomFloat(0.0f, 1.0f), 
        RandomFloat(0.0f, 1.0f), 
        1.0f 
    };
    
    GLfloat specular1[] = {
        RandomFloat(0.0f, 1.0f), 
        RandomFloat(0.0f, 1.0f), 
        RandomFloat(0.0f, 1.0f), 
        1.0f 
    };

    // Apply the random values to light 1
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
}

// Reset flags as appropriate in response to menu selections
void ProcessMenu(int value) {
    if (value < 20) { // magic number 20 is the number of shapes
        iShape = value;
    } else {
        iLight = value - 20;
        if (iLight == 0) {
            glEnable(GL_LIGHT0);
            glDisable(GL_LIGHT1);
        } else if (iLight == 1) {
            SetRandomLight1();
            glEnable(GL_LIGHT1);
            glDisable(GL_LIGHT0);
        }
    }
    glutPostRedisplay();
}

// Called to draw scene
void RenderScene(void) {
    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update light position
    if (iLight == 0) {
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    } else if (iLight == 1) {
        glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
    }

    // Save matrix state and do the rotation
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    // Enable texture if needed
    if (textureEnabled) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);  // Bind the generated texture
    } else {
        glDisable(GL_TEXTURE_2D);  // Disable texture if not enabled
    }

    // Drawing the shape based on the selected menu
    switch (iShape) {
        case 1:
            glutWireSphere(1.0f, 25, 25);
            break;

        case 2:
            glutWireCube(1.0f);
            break;

        case 3:
            glutWireCone(0.30f, 1.1f, 20, 20);
            break;

        case 4:
            glutWireTorus(0.3f, 1.0f, 10, 25);
            break;

        case 5:
            glutWireDodecahedron();
            break;

        case 6:
            glutWireOctahedron();
            break;

        case 7:
            glutWireTetrahedron();
            break;

        case 8:
            glutWireIcosahedron();
            break;

        case 9:
            glutWireTeapot(1.0f);
            break;

        case 11:
            glutSolidSphere(1.0f, 25, 25);
            break;

        case 12:
            glutSolidCube(1.0f);
            break;

        case 13:
            glutSolidCone(0.30, 1.1f, 20, 20);
            break;

        case 14:
            glutSolidTorus(0.3f, 1.0f, 10, 25);
            break;

        case 15:
            glutSolidDodecahedron();
            break;

        case 16:
            glutSolidOctahedron();
            break;

        case 17:
            glutSolidTetrahedron();
            break;

        case 18:
            glutSolidIcosahedron();
            break;

        default:
            glutSolidTeapot(1.0f);
            break;
    }

    // Restore transformations
    glPopMatrix();

    // Flush drawing commands
    glutSwapBuffers();
}

// This function does any needed initialization on the rendering context.
void SetupRC() {
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Enable Depth Testing
    glEnable(GL_DEPTH_TEST);

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Setup and enable light 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glEnable(GL_LIGHT0);

    // Setup and enable light 1
    SetRandomLight1();
    glEnable(GL_LIGHT1);

    glShadeModel(GL_SMOOTH);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // All materials hereafter have full specular reflectivity
    // with a high shine
    glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
    glMateriali(GL_FRONT, GL_SHININESS, 128);

    // Set drawing color to blue
    glColor3ub(0, 0, 255);
}

// Handle special keys for rotation
void SpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP)
        xRot -= 5.0f;

    if (key == GLUT_KEY_DOWN)
        xRot += 5.0f;

    if (key == GLUT_KEY_LEFT)
        yRot -= 5.0f;

    if (key == GLUT_KEY_RIGHT)
        yRot += 5.0f;

    // Clamp rotation values
    if (xRot > 356.0f) xRot = 0.0f;
    if (xRot < -1.0f) xRot = 355.0f;
    if (yRot > 356.0f) yRot = 0.0f;
    if (yRot < -1.0f) yRot = 355.0f;

    // Refresh the Window
    glutPostRedisplay();
}

// Handle WASD keys for light position control
void KeyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            lightPos[1] += 0.1f; // Move light up
            break;
        case 's':
            lightPos[1] -= 0.1f; // Move light down
            break;
        case 'a':
            lightPos[0] -= 0.1f; // Move light left
            break;
        case 'd':
            lightPos[0] += 0.1f; // Move light right
            break;
        default:
            break;
    }
    // Refresh the Window
    glutPostRedisplay();
}

void ChangeSize(int w, int h) {
    GLfloat nRange = 1.9f;

    // Prevent a divide by zero
    if (h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    // Reset projection matrix stack
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h)
        glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
    else
        glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange, nRange);

    // Reset Model view matrix stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main() {
    int nSolidMenu;
    int nWireMenu;
    int nMainMenu;
    int nLightMenu;
    int nTextureMenu;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("GLUT Shapes");

    // Create the Menu
    nWireMenu = glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Sphere", 1);
    glutAddMenuEntry("Cube", 2);
    glutAddMenuEntry("Cone", 3);
    glutAddMenuEntry("Torus", 4);
    glutAddMenuEntry("Dodecahedron", 5);
    glutAddMenuEntry("Octahedron", 6);
    glutAddMenuEntry("Tetrahedron", 7);
    glutAddMenuEntry("Icosahedron", 8);
    glutAddMenuEntry("Teapot", 9);

    nSolidMenu = glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Sphere", 11);
    glutAddMenuEntry("Cube", 12);
    glutAddMenuEntry("Cone", 13);
    glutAddMenuEntry("Torus", 14);
    glutAddMenuEntry("Dodecahedron", 15);
    glutAddMenuEntry("Octahedron", 16);
    glutAddMenuEntry("Tetrahedron", 17);
    glutAddMenuEntry("Icosahedron", 18);
    glutAddMenuEntry("Teapot", 19);

    nLightMenu = glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Light 0", 20);
    glutAddMenuEntry("Light 1", 21);

    nTextureMenu = glutCreateMenu(ToggleTexture);  // Create texture toggle menu
    glutAddMenuEntry("Enable Texture", 1);   // Enable texture
    glutAddMenuEntry("Disable Texture", 0);  // Disable texture

    nMainMenu = glutCreateMenu(ProcessMenu);
    glutAddSubMenu("Wire", nWireMenu);
    glutAddSubMenu("Solid", nSolidMenu);
    glutAddSubMenu("Light", nLightMenu);
    glutAddSubMenu("Texture", nTextureMenu);  // Add texture menu
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutReshapeFunc(ChangeSize);   // Function for changing window size
    glutSpecialFunc(SpecialKeys);  // Function for processing arrow keys
    glutKeyboardFunc(KeyboardFunc);  // Function for processing WASD keys
    glutDisplayFunc(RenderScene);  // Display call
    GenerateTexture();  // Generate the texture
    SetupRC();
    glutMainLoop();
}