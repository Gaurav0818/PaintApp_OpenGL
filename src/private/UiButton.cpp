#include "UiButton.h"

UiButton::UiButton(float a1, float b1, float a2, float b2, eColor color, std::function<void()> onClickEvent)
{
	 x1 = a1;
	 y1 = b1;

	 x2 = a2;
	 y2 = b2;
	 clr = Color();
	 clr = std::move(getColorFromEnum(color));;
	 onButtonClick = std::move(onClickEvent);
}

void UiButton::Draw()
{
	glColor3f(clr.r, clr.g, clr.b);
	glBegin(GL_POLYGON);

	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glVertex2f(x2, y1);

	glEnd();
}

void UiButton::isClicked(const float posX, const float posY)
{
	if (posX >= std::min(x1, x2) && posX <= std::max(x1, x2) && 
		posY >= std::min(y1, y2) && posY <= std::max(y1, y2))
		onButtonClick();
}