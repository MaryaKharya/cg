#pragma once
#include "BaseWindow.h"
#include "SkyBox.h"
#include "Foundation.h"
#include "Facade.h"
#include "Roof.h"
#include "Door.h"
#include "Windows.h"
#include "Lamp.h"
#include "Fence.h"
#include "Floor.h"

class Window : public BaseWindow
{
public:
	Window(int w, int h, const char* title);

private:
	void OnMouseButton(int button, int action, [[maybe_unused]] int mods) override;

	void OnMouseMove(double x, double y) override;

	// ¬ращаем камеру вокруг начала координат
	void RotateCamera(double xAngleRadians, double yAngleRadians);

	void OnResize(int width, int height) override;

	void OnRunStart() override;

	void Draw(int width, int height) override;

	void SetupCameraMatrix();

	SkyBox m_skyBox;
	CFoundation m_foundation;
	CFacade m_facade;
	CRoof m_roof;
	CDoor m_door;
	CWindows m_window;
	CLamp m_lamp;
	CFence m_fence;
	CFloor m_floor;
	// –ассто€ние от камеры до точки вращени€
	static constexpr double DISTANCE_TO_ORIGIN = 2;
	double m_angleX = 0, m_angleY = 0;
	bool m_leftButtonPressed = false;
	glm::dvec2 m_mousePos = {};
	glm::dmat4x4 m_cameraMatrix = glm::lookAt(
		glm::dvec3{ 0.0, 0.0, DISTANCE_TO_ORIGIN },
		glm::dvec3{ 0.0, 0.0, 0.0 },
		glm::dvec3{ 0.0, 1.0, 0.0 });
};
