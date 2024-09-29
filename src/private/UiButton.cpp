#include "UiButton.h"

UiButton::UiButton(float x, float y, float sizeX, float sizeY, eColor color, std::function<void()> onClickEvent)
{
	 m_x = x;
	 m_y = y;

	 m_width = sizeX;
	 m_height = sizeY;
	 m_clr = Color();
	 m_clr = std::move(getColorFromEnum(color));
	 onButtonClick = std::move(onClickEvent);

	 isSelected = false;
}

void UiButton::Draw()
{
	glColor3f(m_clr.r, m_clr.g, m_clr.b);
	glBegin(GL_POLYGON);

	glVertex2f(m_x, m_y);
	glVertex2f(m_x, m_y + m_height);
	glVertex2f(m_x + m_width, m_y + m_height);
	glVertex2f(m_x + m_width, m_y);

	glEnd();

	if (isSelected)
		DrawSelectUI();

}

void UiButton::isClicked(const float posX, const float posY)
{
	if (posX >= std::min(m_x, m_x + m_width) && posX <= std::max(m_x, m_x + m_width) &&
		posY >= std::min(m_y, m_y + m_height) && posY <= std::max(m_y, m_y + m_height))
	{
		onButtonClick();
		isSelected = true;
	}
	else
		isSelected = false;
}

void UiButton::DrawSelectUI()
{
	glPushMatrix();
	glTranslatef(m_x + m_width / 2, m_y + m_height / 2, 0);
	glScalef(0.55, 0.55, 0.55);

	glLineWidth(4);
	glColor3f(0, 0, 0);

	glBegin(GL_LINE_LOOP);
	glVertex2f(-m_width, +m_height);    // Top-left corner
	glVertex2f(-m_width, -m_height);   // Bottom-left corner
	glVertex2f(+m_width, -m_height);    // Bottom-right corner
	glVertex2f(+m_width, +m_height);     // Top-right corner
	glEnd();
	
	glPopMatrix();
}
