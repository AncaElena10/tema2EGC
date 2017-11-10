#pragma once
#include <Component/SimpleScene.h>
#include "LabCamera.h"

class Laborator5 : public SimpleScene
{
	public:
		struct myHero
		{
			myHero() : x(0), y(0), z(0), speed(3.5f), angle(0) {} // eroul are pozitia initiala in centrul scenei
			myHero(float x, float y, float z, float speed, float angle)
				: x(x), y(x), z(z), speed(speed), angle(angle) {}
			float x;
			float y;
			float z;
			float speed;
			float angle;
		};

		struct myEnemy
		{
			myEnemy() : x(-8), y(1), z(-8), length(2.0f), speed(2), life(4), doRotate(false) {} // inamicii apar la pozitia (-8, 1, -8) si au 4 vieti
			myEnemy(float x, float y, float z, float length, float speed, float life, bool doRotate)
				: x(x), y(x), z(z), length(length), speed(speed), life(life), doRotate(doRotate) {}
			float x;
			float y;
			float z;
			float length;
			float speed;
			float life;
			bool doRotate;
		};

		struct firstDef
		{
			firstDef() : x(-5), y(1.7f), z(0) {}
			firstDef(float x, float y, float z, float speed)
				: x(x), y(x), z(z) {}
			float x;
			float y;
			float z;
		};

		struct secondDef
		{
			secondDef() : x(5), y(1.7f), z(0) {}
			secondDef(float x, float y, float z)
				: x(x), y(x), z(z) {}
			float x;
			float y;
			float z;
		};

		struct thirdDef
		{
			thirdDef() : x(0), y(1.7f), z(5) {}
			thirdDef(float x, float y, float z)
				: x(x), y(x), z(z) {}
			float x;
			float y;
			float z;
		};

		struct gun
		{
			gun() : x(0), y(0), z(0), length(0.3f), speed(1.1f), angle(0) {}
			gun(float x, float y, float z, float length, float speed, float angle)
				: x(x), y(x), z(z), length(length), speed(speed), angle(angle) {}
			float x;
			float y;
			float z;
			float length;
			float speed;
			float angle;
		};

		struct fastGun
		{
			fastGun() : x(0), y(0), z(0), length(0.1f), speed(2.0f), angle(0) {}
			fastGun(float x, float y, float z, float length, float speed, float angle)
				: x(x), y(x), z(z), length(length), speed(speed), angle(angle) {}
			float x;
			float y;
			float z;
			float length;
			float speed;
			float angle;
		};

		struct grenade
		{
			grenade() : x(0), y(0), z(0), length(0.5f), speed(0.9f), stop(0), angle(0) {}
			grenade(float x, float y, float z, float length, float speed, int stop, float angle)
				: x(x), y(x), z(z), length(length), speed(speed), stop(stop), angle(angle) {}
			float x;
			float y;
			float z;
			float length;
			float speed;
			int stop;
			float angle;
		};

		struct defenderGun
		{
			defenderGun() : x(0), y(0), z(0), length(0.3f), speed(7.5f), xforCow(0), yforCow(0), zforCow(0) {}
			defenderGun(float x, float y, float z, float length, float speed, float xforCow, float yforCow, float zforCow)
				: x(x), y(x), z(z), length(length), speed(speed), xforCow(xforCow), yforCow(yforCow), zforCow(zforCow) {}
			float x;
			float y;
			float z;
			float length;
			float speed;
			float xforCow;
			float yforCow;
			float zforCow;
		};

		struct defenderGun2
		{
			defenderGun2() : x(0), y(0), z(0), length(0.3f), speed(7.5f), xforCow(0), yforCow(0), zforCow(0) {}
			defenderGun2(float x, float y, float z, float length, float speed, float xforCow, float yforCow, float zforCow)
				: x(x), y(x), z(z), length(length), speed(speed), xforCow(xforCow), yforCow(yforCow), zforCow(zforCow) {}
			float x;
			float y;
			float z;
			float length;
			float speed;
			float xforCow;
			float yforCow;
			float zforCow;
		};

		struct defenderGun3
		{
			defenderGun3() : x(0), y(0), z(0), length(0.3f), speed(7.5f), xforCow(0), yforCow(0), zforCow(0) {}
			defenderGun3(float x, float y, float z, float length, float speed, float xforCow, float yforCow, float zforCow)
				: x(x), y(x), z(z), length(length), speed(speed), xforCow(xforCow), yforCow(yforCow), zforCow(zforCow) {}
			float x;
			float y;
			float z;
			float length;
			float speed;
			float xforCow;
			float yforCow;
			float zforCow;
		};

	public:
		Laborator5();
		~Laborator5();

		void Init() override;

	private:
		void FrameStart() override;
		void GenerateEnemy();
		void RenderFirstDefender();
		void RenderSecondDefender();
		void RenderThirdDefender();
		void GenerateShotgun();
		void GenerateFastShotgun();
		void GenerateGrenade(float deltaTimeSeconds);	
		void GenerateTowerDefense();
		void FirstDef(float deltaTimeSeconds);
		void GenerateTowerDefense2();
		void FirstDef2(float deltaTimeSeconds);
		void GenerateTowerDefense3();
		void FirstDef3(float deltaTimeSeconds);
		void RenderHero(float deltaTimeSeconds);
		void RenderEnemy(float deltaTimeSeconds);
		void RenderLife(float deltaTimeSeconds);
		void CollisionShotgunEnemy();
		void CollisionGrenadeEnemy();
		void CollisionFastShotgunEnemy();
		void CollisionTowerShotgunEnemy();
		void CollisionTowerShotgunEnemy2();
		void CollisionTowerShotgunEnemy3();
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;

	protected:
		Laborator::Camera *camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
		float angularLife1, angularLife2, angularLife3;
		myHero spikeTheHero;
		std::vector<myEnemy> cowTheEnemy;
		std::vector<gun> shotgun;
		std::vector<grenade> grenadeBANG;
		std::vector<fastGun> fastShotgun;
		std::vector<defenderGun> defGun;
		std::vector<defenderGun2> defGun2;
		std::vector<defenderGun3> defGun3;
		firstDef firstDefender;
		secondDef secondDefender;
		thirdDef thirdDefender;
};
