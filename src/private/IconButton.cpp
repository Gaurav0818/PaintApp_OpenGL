#include "IconButton.h"

void IconButton::Draw()
{
    UiButton::Draw();
    DrawIcon();
}

void IconButton::DrawIcon()
{
    switch (m_tool) {
    case eToolType::PencilTool:
        drawPencilIcon(m_x, m_y, m_width, m_height);
        break;
    case eToolType::LineTool:
        drawLineIcon(m_x, m_y, m_width);
        break;
    case eToolType::EraserTool:
        drawEraserIcon(m_x, m_y, m_width, m_height);
        break;
    case eToolType::BucketTool:
        drawBucketIcon(m_x, m_y, m_width, m_height);
        break;
    case eToolType::RectTool:
        drawRectangleIcon(m_x, m_y, m_width, m_height);
        break;
    default:
        break;
    }
}

void IconButton::drawPencilIcon(float x, float y, float width, float height)
{
    glPushMatrix();
    glTranslatef(x+ width / 4 * 3, y + height / 4 * 3, 0.0f);
    glScalef(0.5f, 0.5f, 1.0f);
    glRotatef(-45, 0, 0, 1);

    glColor3f(0.0f, 0.0f, 0.0f);  
    glBegin(GL_POLYGON);
    glVertex2f(-width / 2, -height);  // Bottom-left
    glVertex2f(-width / 2, 0.0f);    // Top-left
    glVertex2f(width / 2, 0.0f);     // Top-right
    glVertex2f(width / 2, -height);  // Bottom-right
    glEnd();


    glBegin(GL_TRIANGLES);
    float triangleBase = width;
    float triangleHeight = 0.0866f;
    glVertex2f(-triangleBase / 2, -height);                     
    glVertex2f(triangleBase / 2, -height);                      
    glVertex2f(0.0f, -height - triangleHeight);                 
    glEnd();


    glPopMatrix();
}

void IconButton::drawLineIcon(float x, float y, float length)
{
    glPushMatrix();
    glTranslatef(x + length/2, y + length/2, 0.0f);
    glScalef(0.5f, 0.5f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(-length / 2, length / 2);   // Start point
    glVertex2f(length / 2, -length / 2);   // End point
    glEnd();

    glPopMatrix();
}

void IconButton::drawEraserIcon(float x, float y, float width, float height)
{
    glPushMatrix();
    glTranslatef(x + width / 2, y + height / 2, 0.0f);
    glScalef(0.25f, 0.25f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    
    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-width - 0.05, height - 0.01);       // Top-left
    glVertex2f(-width - 0.05, -height + 0.015);     // Bottom-left
    glVertex2f(width - 0.05, -height + 0.015);      // Bottom-right
    glVertex2f(width - 0.05, height - 0.01);        // Top-right
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-width, height);    // Top-left
    glVertex2f(-width, -height);   // Bottom-left
    glVertex2f(width, -height);    // Bottom-right
    glVertex2f(width, height);     // Top-right
    glEnd();

    glPopMatrix();
}

void IconButton::drawBucketIcon(float x, float y, float width, float height)
{
    glPushMatrix();
    glTranslatef(x + width / 2, y + height / 2, 0.0f);
    glScalef(0.25f, 0.25f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glLineWidth(1);
    glBegin(GL_LINE_LOOP);

    int numSegments = 10;
    for (int i = 0; i < numSegments; i++)
    {
        float angle = 2.0f * 3.14159f * float(i) / float(numSegments);
        float posX = width/3 * 2 * cos(angle);
        float posY = width/3 * 2 * sin(angle);
        glVertex2f(posX, height + posY);
    }

    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-width, +height);    // Top-left corner
    glVertex2f(-width/2, -height);   // Bottom-left corner
    glVertex2f(+width/2, -height);    // Bottom-right corner
    glVertex2f(+width, +height);     // Top-right corner
    glEnd();

    glPopMatrix();
}

void IconButton::drawRectangleIcon(float x, float y, float width, float height)
{
    glPushMatrix();
    glTranslatef(x + width / 2, y + height / 2, 0.0f);
    glScalef(0.25f, 0.25f, 1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-width, +height);    // Top-left corner
    glVertex2f(-width, -height);   // Bottom-left corner
    glVertex2f(+width, -height);    // Bottom-right corner
    glVertex2f(+width, +height);     // Top-right corner
    glEnd();

    glPopMatrix();
}