#include "ButtonConfig.h"
#include "../ToolHandler.h"

ButtonConfig::ButtonConfig(ToolType action, int color, ToolSize size,
                           DrawingType drawingType, EraserType eraserMode)
{
	XOJ_INIT_TYPE(ButtonConfig);

	this->action = action;
	this->color = color;
	this->size = size;
	this->drawingType = drawingType;
	this->eraserMode = eraserMode;
	this->disableDrawing = false;
}

ButtonConfig::~ButtonConfig()
{
	XOJ_RELEASE_TYPE(ButtonConfig);
}


bool ButtonConfig::getDisableDrawing()
{
	XOJ_CHECK_TYPE(ButtonConfig);

	return this->disableDrawing;
}

DrawingType ButtonConfig::getDrawingType()
{
	XOJ_CHECK_TYPE(ButtonConfig);

	return this->drawingType;
}

ToolType ButtonConfig::getAction()
{
	XOJ_CHECK_TYPE(ButtonConfig);

	return this->action;
}

void ButtonConfig::acceptActions(ToolHandler* toolHandler)
{
	XOJ_CHECK_TYPE(ButtonConfig);

	if (this->action != TOOL_NONE)
	{
		toolHandler->selectTool(this->action, false);

		if (this->action == TOOL_PEN || this->action == TOOL_HILIGHTER)
		{

			if (this->drawingType == DRAWING_TYPE_DONT_CHANGE)
			{
				// nothing to do
			}
			else if (this->drawingType == DRAWING_TYPE_STROKE_RECOGNIZER)
			{
				toolHandler->setRuler(false);
				toolHandler->setRectangle(false);
				toolHandler->setCircle(false);
				toolHandler->setArrow(false);
				toolHandler->setShapeRecognizer(true);
			}
			else if (this->drawingType == DRAWING_TYPE_RULER)
			{
				toolHandler->setRuler(true);
				toolHandler->setRectangle(false);
				toolHandler->setCircle(false);
				toolHandler->setArrow(false);
				toolHandler->setShapeRecognizer(false);
			}
			else if (this->drawingType == DRAWING_TYPE_RECTANGLE)
			{
				toolHandler->setRuler(false);
				toolHandler->setRectangle(true);
				toolHandler->setCircle(false);
				toolHandler->setArrow(false);
				toolHandler->setShapeRecognizer(false);
			}
			else if (this->drawingType == DRAWING_TYPE_CIRCLE)
			{
				toolHandler->setRuler(false);
				toolHandler->setRectangle(false);
				toolHandler->setCircle(true);
				toolHandler->setArrow(false);
				toolHandler->setShapeRecognizer(false);
			}
			else if (this->drawingType == DRAWING_TYPE_ARROW)
			{
				toolHandler->setRuler(false);
				toolHandler->setRectangle(false);
				toolHandler->setCircle(false);
				toolHandler->setArrow(true);
				toolHandler->setShapeRecognizer(false);
			}
			else if (this->drawingType == DRAWING_TYPE_NONE)
			{
				toolHandler->setRuler(false);
				toolHandler->setRectangle(false);
				toolHandler->setCircle(false);
				toolHandler->setArrow(false);
				toolHandler->setShapeRecognizer(false);
			}

			if (this->size != TOOL_SIZE_NONE)
			{
				toolHandler->setSize(this->size);
			}
		}

		if (this->action == TOOL_PEN || this->action == TOOL_HILIGHTER ||
		    this->action == TOOL_TEXT)
		{
			toolHandler->setColor(this->color);
		}

		if (this->action == TOOL_ERASER && this->eraserMode != ERASER_TYPE_NONE)
		{
			toolHandler->setEraserType(this->eraserMode);
		}

		toolHandler->fireToolChanged();
	}
}
