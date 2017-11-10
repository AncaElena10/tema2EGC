#include "Laborator5.h"
#include "Transform3D.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

bool first = true, second = true, third = true;
double actualTime = Engine::GetElapsedTime();
float lastTime = 0.0f;
float intervalBetween = 5.0f;
float goShot = 0.1f;
bool shotGunON = false;
bool grenadeON = false;
bool fastShotgunON = false;
float up = 1.0f;
float camAngle = 25;
bool renderHero = true;
int grenadeDist = 4;
float animTime = 0.0f;
float maxAngle = RADIANS(0);
float heroAnimTime = 0.0f;
float heroMaxAngle = RADIANS(0);
bool renderShotgun = true;
bool renderGrenade = true;
bool renderFastShotgun = true;
double actualTimeTower = Engine::GetElapsedTime();
float oneSecond = 1.0f;
double actualTimeTower2 = Engine::GetElapsedTime();
float oneSecond2 = 1.0f;
double actualTimeTower3 = Engine::GetElapsedTime();
float oneSecond3 = 1.0f;

Laborator5::Laborator5()
{
}

Laborator5::~Laborator5()
{
}

void Laborator5::Init()
{
	renderCameraTarget = false;

	camera = new Laborator::Camera();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	{
		Mesh* mesh = new Mesh("spike");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "spike.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("life");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("cow");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "cow.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("defender");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "tower.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("shotgun");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	angularLife1 = 0.0f;
	angularLife2 = 0.0f;
	angularLife3 = 0.0f;
}

void Laborator5::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator5::GenerateEnemy() 

{
	if (actualTime < Engine::GetElapsedTime() - intervalBetween) {
		if (intervalBetween >= 0.5f) {
			intervalBetween -= 0.04f;
		}

		myEnemy enemyObject;
		cowTheEnemy.push_back(enemyObject);
		actualTime = Engine::GetElapsedTime();
	}
}

void Laborator5::RenderFirstDefender() 
{
	glm::mat4 modelMatrix = glm::mat4(1);

	modelMatrix *= Transform3D::Translate(firstDefender.x, 0, 0);
	modelMatrix *= Transform3D::Scale(0.004f, 0.004f, 0.004f);
	RenderMesh(meshes["defender"], shaders["VertexNormal"], modelMatrix);
}

void Laborator5::RenderSecondDefender()
{
	glm::mat4 modelMatrix = glm::mat4(1);

	modelMatrix *= Transform3D::Translate(secondDefender.x, 0, 0);
	modelMatrix *= Transform3D::Scale(0.004f, 0.004f, 0.004f);
	RenderMesh(meshes["defender"], shaders["VertexNormal"], modelMatrix);
}

void Laborator5::RenderThirdDefender()
{
	glm::mat4 modelMatrix = glm::mat4(1);

	modelMatrix *= Transform3D::Translate(0, 0, thirdDefender.z);
	modelMatrix *= Transform3D::Scale(0.004f, 0.004f, 0.004f);
	RenderMesh(meshes["defender"], shaders["VertexNormal"], modelMatrix);
}

void Laborator5::GenerateShotgun() 
{
	for (int i = 0; i < shotgun.size(); i++) {
		glm::mat4 modelMatrix = glm::mat4(1);
		shotgun[i].x -= goShot * sin(shotgun[i].angle) * shotgun[i].speed;
		shotgun[i].z -= goShot * cos(shotgun[i].angle) * shotgun[i].speed;

		modelMatrix *= Transform3D::Translate(shotgun[i].x, shotgun[i].y + 1.0f, shotgun[i].z);
		modelMatrix *= Transform3D::Scale(0.3f, 0.3f, 0.3f);
		RenderMesh(meshes["shotgun"], shaders["Simple"], modelMatrix);
	}

	// pistolul trage pe o distanta mai mica
	for (int i = 0; i < shotgun.size(); i++) {
		if (shotgun[i].z < (spikeTheHero.z - 7.0f) || shotgun[i].x < (spikeTheHero.x - 7.0f) || 
			shotgun[i].z > (spikeTheHero.z + 7.0f) || shotgun[i].x > (spikeTheHero.x + 7.0f)) {
			shotgun.erase(shotgun.begin() + i);
		}
	}
}

void Laborator5::GenerateFastShotgun() 
{
	for (int i = 0; i < fastShotgun.size(); i++) {
		glm::mat4 modelMatrix = glm::mat4(1);
		fastShotgun[i].x -= goShot * sin(fastShotgun[i].angle) * fastShotgun[i].speed;
		fastShotgun[i].z -= goShot * cos(fastShotgun[i].angle) * fastShotgun[i].speed;

		modelMatrix *= Transform3D::Translate(fastShotgun[i].x, fastShotgun[i].y + 1.0f, fastShotgun[i].z);
		modelMatrix *= Transform3D::Scale(0.1f, 0.1f, 0.1f);
		RenderMesh(meshes["shotgun"], shaders["Simple"], modelMatrix);
	}

	// pusca trage pe o distanta mai mare
	for (int i = 0; i < fastShotgun.size(); i++) {
		if (fastShotgun[i].z < (spikeTheHero.z - 30.0f) || fastShotgun[i].x < (spikeTheHero.x - 30.0f) || 
			fastShotgun[i].z > (spikeTheHero.z + 30.0f) || fastShotgun[i].x > (spikeTheHero.x + 30.0f)) {
			fastShotgun.erase(fastShotgun.begin() + i);
		}
	}
}

void Laborator5::GenerateGrenade(float deltaTimeSeconds) 
{
	for (int i = 0; i < grenadeBANG.size(); i++) {
		glm::mat4 modelMatrix = glm::mat4(1);

		if (grenadeBANG[i].stop == 0) {
			grenadeBANG[i].x -= grenadeDist * deltaTimeSeconds * sin(grenadeBANG[i].angle) * grenadeBANG[i].speed;
			grenadeBANG[i].z -= grenadeDist * deltaTimeSeconds * cos(grenadeBANG[i].angle) * grenadeBANG[i].speed;
			grenadeBANG[i].y += deltaTimeSeconds * grenadeBANG[i].speed;

			if (grenadeBANG[i].y >= up) {
				grenadeBANG[i].stop = 1;
			}
		}

		if (grenadeBANG[i].stop == 1) {
			grenadeBANG[i].x -= grenadeDist * deltaTimeSeconds * sin(grenadeBANG[i].angle) * grenadeBANG[i].speed;
			grenadeBANG[i].z -= grenadeDist * deltaTimeSeconds * cos(grenadeBANG[i].angle) * grenadeBANG[i].speed;
			grenadeBANG[i].y -= deltaTimeSeconds * grenadeBANG[i].speed;

			if (grenadeBANG[i].y <= -1) {
				grenadeBANG[i].stop = 0;
				grenadeBANG.erase(grenadeBANG.begin() + i);
				continue;
			}
		}

		modelMatrix *= Transform3D::Translate(grenadeBANG[i].x, grenadeBANG[i].y + 1.0f, grenadeBANG[i].z);
		modelMatrix *= Transform3D::Scale(0.5f, 0.5f, 0.5f);
		RenderMesh(meshes["shotgun"], shaders["Simple"], modelMatrix);
	}
}

void Laborator5::GenerateTowerDefense() {
	for (int i = 0; i < cowTheEnemy.size(); i++) {
		float isClose = (firstDefender.x - cowTheEnemy[i].x) * (firstDefender.x - cowTheEnemy[i].x) +
						(firstDefender.z - cowTheEnemy[i].z) * (firstDefender.z - cowTheEnemy[i].z);

		if (isClose <= 18) {
			if (actualTimeTower < Engine::GetElapsedTime() - oneSecond) {
				if (oneSecond >= 1.0f) {
					oneSecond -= 0.0f;
				}

				defenderGun defGunObject;
				defGunObject.x = firstDefender.x;
				defGunObject.y = firstDefender.y;
				defGunObject.z = firstDefender.z;
				defGunObject.xforCow = cowTheEnemy[i].x;
				defGunObject.yforCow = cowTheEnemy[i].y;
				defGunObject.zforCow = cowTheEnemy[i].z;
				defGun.push_back(defGunObject);

				actualTimeTower = Engine::GetElapsedTime();
			}
		}
	}
}

void Laborator5::FirstDef(float deltaTimeSeconds) 
{
	for (int i = 0; i < defGun.size(); i++) {
		float distance = sqrt((firstDefender.x - defGun[i].xforCow) * (firstDefender.x - defGun[i].xforCow) + 
							  (firstDefender.x - defGun[i].zforCow) * (firstDefender.x - defGun[i].zforCow));
		float gunX = (-firstDefender.x + defGun[i].xforCow) / distance;
		float gunZ = (-firstDefender.z + defGun[i].zforCow) / distance;

		defGun[i].x += deltaTimeSeconds * defGun[i].speed * gunX;
		defGun[i].y -= deltaTimeSeconds * defGun[i].speed * sin(RADIANS(15));
		defGun[i].z += deltaTimeSeconds * defGun[i].speed * gunZ;

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(defGun[i].x, defGun[i].y, defGun[i].z);
		modelMatrix *= Transform3D::Scale(0.3f, 0.3f, 0.3f);
		RenderMesh(meshes["shotgun"], shaders["VertexNormal"], modelMatrix);
	}
	for (int i = 0; i < defGun.size(); i++) {
		if (defGun[i].z < - 30.0f || defGun[i].x < - 30.0f || defGun[i].z > 30.0f || defGun[i].x > 30.0f) {
			defGun.erase(defGun.begin() + i);
			return;
		}
	}
}

void Laborator5::GenerateTowerDefense2() {
	for (int i = 0; i < cowTheEnemy.size(); i++) {
		float isClose = (secondDefender.x - cowTheEnemy[i].x) * (secondDefender.x - cowTheEnemy[i].x) +
						(secondDefender.z - cowTheEnemy[i].z) * (secondDefender.z - cowTheEnemy[i].z);

		if (isClose <= 18) {
			if (actualTimeTower2 < Engine::GetElapsedTime() - oneSecond2) {
				if (oneSecond2 >= 1.0f) {
					oneSecond2 -= 0.0f;
				}

				defenderGun2 defGunObject2;
				defGunObject2.x = secondDefender.x;
				defGunObject2.y = secondDefender.y;
				defGunObject2.z = secondDefender.z;
				defGunObject2.xforCow = cowTheEnemy[i].x;
				defGunObject2.yforCow = cowTheEnemy[i].y;
				defGunObject2.zforCow = cowTheEnemy[i].z;
				defGun2.push_back(defGunObject2);

				actualTimeTower2 = Engine::GetElapsedTime();
			}
		}
	}
}

void Laborator5::FirstDef2(float deltaTimeSeconds)
{
	for (int i = 0; i < defGun2.size(); i++) {
		float distance = sqrt((secondDefender.x - defGun2[i].xforCow) * (secondDefender.x - defGun2[i].xforCow) +
							  (secondDefender.x - defGun2[i].zforCow) * (secondDefender.x - defGun2[i].zforCow));
		float gunX = (-secondDefender.x + defGun2[i].xforCow) / distance;
		float gunZ = (-secondDefender.z + defGun2[i].zforCow) / distance;

		defGun2[i].x += deltaTimeSeconds * defGun2[i].speed * gunX;
		defGun2[i].y -= deltaTimeSeconds * defGun2[i].speed * sin(RADIANS(15));
		defGun2[i].z += deltaTimeSeconds * defGun2[i].speed * gunZ;

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(defGun2[i].x, defGun2[i].y, defGun2[i].z);
		modelMatrix *= Transform3D::Scale(0.3f, 0.3f, 0.3f);
		RenderMesh(meshes["shotgun"], shaders["VertexNormal"], modelMatrix);
	}

	for (int i = 0; i < defGun2.size(); i++) {
		if (defGun2[i].z < -30.0f || defGun2[i].x < -30.0f || defGun2[i].z > 30.0f || defGun2[i].x > 30.0f) {
			defGun2.erase(defGun2.begin() + i);
			return;
		}
	}
}


void Laborator5::GenerateTowerDefense3() {
	for (int i = 0; i < cowTheEnemy.size(); i++) {
		float isClose = (thirdDefender.x - cowTheEnemy[i].x) * (thirdDefender.x - cowTheEnemy[i].x) +
						(thirdDefender.z - cowTheEnemy[i].z) * (thirdDefender.z - cowTheEnemy[i].z);

		if (isClose <= 18) {
			if (actualTimeTower3 < Engine::GetElapsedTime() - oneSecond3) {
				if (oneSecond3 >= 1.0f) {
					oneSecond3 -= 0.0f;
				}

				defenderGun3 defGunObject3;
				defGunObject3.x = thirdDefender.x;
				defGunObject3.y = thirdDefender.y;
				defGunObject3.z = thirdDefender.z;
				defGunObject3.xforCow = cowTheEnemy[i].x;
				defGunObject3.yforCow = cowTheEnemy[i].y;
				defGunObject3.zforCow = cowTheEnemy[i].z;
				defGun3.push_back(defGunObject3);

				actualTimeTower3 = Engine::GetElapsedTime();
			}
		}
	}
}

void Laborator5::FirstDef3(float deltaTimeSeconds)
{
	for (int i = 0; i < defGun3.size(); i++) {
		float distance = sqrt((thirdDefender.x - defGun3[i].xforCow) * (thirdDefender.x - defGun3[i].xforCow) +
							  (thirdDefender.x - defGun3[i].zforCow) * (thirdDefender.x - defGun3[i].zforCow));
		float gunX = (-thirdDefender.x + defGun3[i].xforCow) / distance;
		float gunZ = (-thirdDefender.z + defGun3[i].zforCow) / distance;

		defGun3[i].x += deltaTimeSeconds * defGun3[i].speed * gunX;
		defGun3[i].y -= deltaTimeSeconds * defGun3[i].speed * sin(RADIANS(15));
		defGun3[i].z += deltaTimeSeconds * defGun3[i].speed * gunZ;

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(defGun3[i].x, defGun3[i].y, defGun3[i].z);
		modelMatrix *= Transform3D::Scale(0.3f, 0.3f, 0.3f);
		RenderMesh(meshes["shotgun"], shaders["VertexNormal"], modelMatrix);
	}

	for (int i = 0; i < defGun3.size(); i++) {
		if (defGun3[i].z < -30.0f || defGun3[i].x < -30.0f || defGun3[i].z > 30.0f || defGun3[i].x > 30.0f) {
			defGun3.erase(defGun3.begin() + i);
			return;
		}
	}
}


void Laborator5::RenderHero(float deltaTimeSeconds)
{
	float rotationAngle = RADIANS(180);
	glm::mat4 modelMatrix = glm::mat4(1);

	modelMatrix *= Transform3D::Translate(spikeTheHero.x, spikeTheHero.y, spikeTheHero.z);
	modelMatrix *= Transform3D::Scale(0.014f, 0.014f, 0.014f);
	modelMatrix *= Transform3D::RotateOY((spikeTheHero.angle) + rotationAngle);

	// sfarsitul jocului
	if (first == false && second == false && third == false) {
		if (heroAnimTime <= 1.5f) {
			modelMatrix *= Transform3D::RotateOZ(heroMaxAngle);
			if (heroMaxAngle <= RADIANS(90)) {
				heroMaxAngle += deltaTimeSeconds * 0.8f;
			}
			heroAnimTime += deltaTimeSeconds;
		}
		else {
			modelMatrix *= Transform3D::RotateOZ(RADIANS(90));
		}

		spikeTheHero.speed = 0;
		renderFastShotgun = false;
		renderGrenade = false;
		renderShotgun = false;
	}
	RenderMesh(meshes["spike"], shaders["VertexNormal"], modelMatrix); 
}

void Laborator5::RenderEnemy(float deltaTimeSeconds)
{
	for (int i = 0; i < cowTheEnemy.size(); i++) {
		glm::mat4 modelMatrix = glm::mat4(1);

		float angularCow1 = RADIANS(225); // unghi de rotire al inamicului

		modelMatrix *= Transform3D::Translate(cowTheEnemy[i].x, cowTheEnemy[i].y, cowTheEnemy[i].z); // pozitia initiala inamic
		modelMatrix *= Transform3D::Scale(0.34f, 0.34f, 0.34f);

		if (cowTheEnemy[i].x <= 8 && cowTheEnemy[i].z == -8) {
			cowTheEnemy[i].x += deltaTimeSeconds * cowTheEnemy[i].speed;
		}

		if (cowTheEnemy[i].x >= 8 && cowTheEnemy[i].z < 8) {
			cowTheEnemy[i].x -= deltaTimeSeconds * cowTheEnemy[i].speed;
			cowTheEnemy[i].z += deltaTimeSeconds * cowTheEnemy[i].speed;
		}

		if (cowTheEnemy[i].z > -8 && cowTheEnemy[i].z < 8 && cowTheEnemy[i].x < 8) {
			cowTheEnemy[i].x -= deltaTimeSeconds * cowTheEnemy[i].speed;
			cowTheEnemy[i].z += deltaTimeSeconds * cowTheEnemy[i].speed;
			modelMatrix *= Transform3D::RotateOY(angularCow1);
			modelMatrix *= Transform3D::Translate(-cowTheEnemy[i].x, 1, -cowTheEnemy[i].z);
		}

		if (cowTheEnemy[i].x <= 8 && cowTheEnemy[i].z >= 8) {
			cowTheEnemy[i].x += deltaTimeSeconds * cowTheEnemy[i].speed;
		}

		if (cowTheEnemy[i].x >= 8 && cowTheEnemy[i].z >= 8) { // cand inamicul ajunge la capatul labirintului, dispare si eroul pierde o viata
			cowTheEnemy.erase(cowTheEnemy.begin() + i);

			if (first == true && second == false && third == false) {
				first = false;
			}
			if (first == true && second == true && third == false) {
				second = false;
			}
			third = false;
			continue;
		}

		modelMatrix *= Transform3D::Translate(cowTheEnemy[i].x, cowTheEnemy[i].y, cowTheEnemy[i].z);
		if (cowTheEnemy[i].doRotate == true) {
			if (animTime <= 1.5f) {
				modelMatrix *= Transform3D::RotateOX(maxAngle);
				if (maxAngle <= RADIANS(90)) {
					maxAngle += deltaTimeSeconds * 0.8f;
				}
				animTime += deltaTimeSeconds;
			}
			else {
				modelMatrix *= Transform3D::RotateOX(RADIANS(90));
				cowTheEnemy.erase(cowTheEnemy.begin() + i);
				animTime = 0.0f;
				maxAngle = RADIANS(0);
				continue;
			}
		}
		RenderMesh(meshes["cow"], shaders["VertexNormal"], modelMatrix);
	}
}

void Laborator5::RenderLife(float deltaTimeSeconds)
{
	if (first == true) {
		angularLife1 += deltaTimeSeconds;
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(spikeTheHero.x, spikeTheHero.y + 1.1f, spikeTheHero.z);
		modelMatrix *= Transform3D::RotateOX(angularLife1);
		modelMatrix *= Transform3D::Translate(0, spikeTheHero.y + 1.18f, 0);
		modelMatrix *= Transform3D::Scale(0.3f, 0.3f, 0.3f);
		RenderMesh(meshes["life"], shaders["Simple"], modelMatrix);
	}

	if (second == true) {
		angularLife2 += deltaTimeSeconds;
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(spikeTheHero.x, spikeTheHero.y + 1.0f, spikeTheHero.z);
		modelMatrix *= Transform3D::RotateOY(angularLife2);
		modelMatrix *= Transform3D::Translate(1, 0, 0);
		modelMatrix *= Transform3D::Scale(0.3f, 0.3f, 0.3f);
		RenderMesh(meshes["life"], shaders["Simple"], modelMatrix);
	}

	if (third == true) {
		angularLife3 += deltaTimeSeconds;
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(spikeTheHero.x, spikeTheHero.y + 0.8f, spikeTheHero.z);
		modelMatrix *= Transform3D::RotateOZ(angularLife3);
		modelMatrix *= Transform3D::Translate(1, -0.8f, 0);
		modelMatrix *= Transform3D::Scale(0.3f, 0.3f, 0.3f);
		RenderMesh(meshes["life"], shaders["Simple"], modelMatrix);
	}
}

void Laborator5::CollisionShotgunEnemy() 
{
	for (int i = 0; i < cowTheEnemy.size(); i++) {
		for (int j = 0; j < shotgun.size(); j++) {
			if (abs(cowTheEnemy[i].x - shotgun[j].x) < cowTheEnemy[i].length + shotgun[j].length - 2.0f) {
				if (abs(cowTheEnemy[i].x - shotgun[j].x) < cowTheEnemy[i].length + shotgun[j].length - 2.0f) {
					if (abs(cowTheEnemy[i].x - shotgun[j].x) < cowTheEnemy[i].length + shotgun[j].length - 2.0f) {
						shotgun.erase(shotgun.begin() + j);
						
						cowTheEnemy[i].life = cowTheEnemy[i].life - 2;

						if (cowTheEnemy[i].life <= 0) {
							cowTheEnemy[i].speed = 0;
							cowTheEnemy[i].doRotate = true;
						}
						return;
					}
				}
			}
		}
	}
}

void Laborator5::CollisionGrenadeEnemy() 
{
	for (int i = 0; i < cowTheEnemy.size(); i++) {
		for (int j = 0; j < grenadeBANG.size(); j++) {
			if (abs(cowTheEnemy[i].x - grenadeBANG[j].x) < cowTheEnemy[i].length + grenadeBANG[j].length - 2.1f) {
				if (abs(cowTheEnemy[i].x - grenadeBANG[j].x) < cowTheEnemy[i].length + grenadeBANG[j].length - 2.1f ) {
					if (abs(cowTheEnemy[i].x - grenadeBANG[j].x) < cowTheEnemy[i].length + grenadeBANG[j].length -2.1f ) {
						grenadeBANG.erase(grenadeBANG.begin() + j);

						cowTheEnemy[i].life = 0;

						if (cowTheEnemy[i].life <= 0) {
							cowTheEnemy[i].speed = 0;
							cowTheEnemy[i].doRotate = true;
						}
						return;
					}
				}
			}
		}
	}
}

void Laborator5::CollisionFastShotgunEnemy() 
{
	for (int i = 0; i < cowTheEnemy.size(); i++) {
		for (int j = 0; j < fastShotgun.size(); j++) {
			if (abs(cowTheEnemy[i].x - fastShotgun[j].x) < cowTheEnemy[i].length + fastShotgun[j].length - 2.0f) {
				if (abs(cowTheEnemy[i].x - fastShotgun[j].x) < cowTheEnemy[i].length + fastShotgun[j].length - 2.0f) {
					if (abs(cowTheEnemy[i].x - fastShotgun[j].x) < cowTheEnemy[i].length + fastShotgun[j].length - 2.0f) {
						fastShotgun.erase(fastShotgun.begin() + j);
						
						cowTheEnemy[i].life = cowTheEnemy[i].life - 0.5f;

						if (cowTheEnemy[i].life <= 0) {
							cowTheEnemy[i].speed = 0;
							cowTheEnemy[i].doRotate = true;
						}
						return;
					}
				}
			}
		}
	}

}

void Laborator5::CollisionTowerShotgunEnemy()
{
	for (int i = 0; i < cowTheEnemy.size(); i++) {
		for (int j = 0; j < defGun.size(); j++) {
			if (abs(cowTheEnemy[i].x - defGun[j].x) < cowTheEnemy[i].length + defGun[j].length - 2.0f) {
				if (abs(cowTheEnemy[i].x - defGun[j].x) < cowTheEnemy[i].length + defGun[j].length - 2.0f) {
					if (abs(cowTheEnemy[i].x - defGun[j].x) < cowTheEnemy[i].length + defGun[j].length - 2.0f) {
						defGun.erase(defGun.begin() + j);

						cowTheEnemy[i].life = cowTheEnemy[i].life - 1;

						if (cowTheEnemy[i].life <= 0) {
							cowTheEnemy[i].speed = 0;
							cowTheEnemy[i].doRotate = true;
						}
						return;
					}
				}
			}
		}
	}
}

void Laborator5::CollisionTowerShotgunEnemy2()
{
	for (int i = 0; i < cowTheEnemy.size(); i++) {
		for (int j = 0; j < defGun2.size(); j++) {
			if (abs(cowTheEnemy[i].x - defGun2[j].x) < cowTheEnemy[i].length + defGun2[j].length - 2.0f) {
				if (abs(cowTheEnemy[i].x - defGun2[j].x) < cowTheEnemy[i].length + defGun2[j].length - 2.0f) {
					if (abs(cowTheEnemy[i].x - defGun2[j].x) < cowTheEnemy[i].length + defGun2[j].length - 2.0f) {
						defGun2.erase(defGun2.begin() + j);

						cowTheEnemy[i].life = cowTheEnemy[i].life - 1;

						if (cowTheEnemy[i].life <= 0) {
							cowTheEnemy[i].speed = 0;
							cowTheEnemy[i].doRotate = true;
						}
						return;
					}
				}
			}
		}
	}
}

void Laborator5::CollisionTowerShotgunEnemy3()
{
	for (int i = 0; i < cowTheEnemy.size(); i++) {
		for (int j = 0; j < defGun3.size(); j++) {
			if (abs(cowTheEnemy[i].x - defGun3[j].x) < cowTheEnemy[i].length + defGun3[j].length - 2.0f) {
				if (abs(cowTheEnemy[i].x - defGun3[j].x) < cowTheEnemy[i].length + defGun3[j].length - 2.0f) {
					if (abs(cowTheEnemy[i].x - defGun3[j].x) < cowTheEnemy[i].length + defGun3[j].length - 2.0f) {
						defGun3.erase(defGun3.begin() + j);

						cowTheEnemy[i].life = cowTheEnemy[i].life - 1;

						if (cowTheEnemy[i].life <= 0) {
							cowTheEnemy[i].speed = 0;
							cowTheEnemy[i].doRotate = true;
						}
						return;
					}
				}
			}
		}
	}
}

void Laborator5::Update(float deltaTimeSeconds)
{
	// generare inamici la fiecare 5 secunde, apoi timpul scade
	GenerateEnemy();

	// randare primul ajutor
	RenderFirstDefender();

	// randare al doilea ajutor
	RenderSecondDefender();

	// randare al treilea ajutor
	RenderThirdDefender();

	// randare erou
	if (renderHero == true) {
		RenderHero(deltaTimeSeconds);
	}

	// randare pistol
	if (renderShotgun == true) {
		GenerateShotgun();
	}

	// randare pusca
	if (renderFastShotgun == true) {
		GenerateFastShotgun();
	}

	// randare grenada
	if (renderGrenade == true) {
		GenerateGrenade(deltaTimeSeconds);
	}

	// randare vieti
	RenderLife(deltaTimeSeconds);

	// randare inamici
	RenderEnemy(deltaTimeSeconds);	

	// verificare coliziune pistol-inamic
	CollisionShotgunEnemy();

	// verificare coliziune pusca-inamic
	CollisionFastShotgunEnemy();
	
	// verificare coliziune grenada-inamic
	CollisionGrenadeEnemy();

	GenerateTowerDefense();

	FirstDef(deltaTimeSeconds);

	GenerateTowerDefense2();

	FirstDef2(deltaTimeSeconds);

	GenerateTowerDefense3();

	FirstDef3(deltaTimeSeconds);

	CollisionTowerShotgunEnemy();

	CollisionTowerShotgunEnemy2();

	CollisionTowerShotgunEnemy3();
}

void Laborator5::FrameEnd()
{
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Laborator5::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void Laborator5::OnInputUpdate(float deltaTime, int mods)
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 3.5f;

		// miscare camera o data cu eroul
		if (window->KeyHold(GLFW_KEY_W)) {
			spikeTheHero.z -= deltaTime * cameraSpeed * cos(spikeTheHero.angle);
			spikeTheHero.x -= deltaTime * cameraSpeed * sin(spikeTheHero.angle);
			camera->MoveForward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			spikeTheHero.x -= deltaTime * cameraSpeed * cos(spikeTheHero.angle);
			spikeTheHero.z += deltaTime * cameraSpeed * sin(spikeTheHero.angle);
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			spikeTheHero.z += deltaTime * cameraSpeed * cos(spikeTheHero.angle);
			spikeTheHero.x += deltaTime * cameraSpeed * sin(spikeTheHero.angle);
			camera->MoveForward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			spikeTheHero.x += deltaTime * cameraSpeed * cos(spikeTheHero.angle);
			spikeTheHero.z -= deltaTime * cameraSpeed * sin(spikeTheHero.angle);
			camera->TranslateRight(deltaTime * cameraSpeed);
		}
	}
}

void Laborator5::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}

	if (key == GLFW_KEY_1) {
		renderHero = true;
		projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
		shotGunON = true;
	}

	if (key == GLFW_KEY_2) {
		renderHero = false;
		projectionMatrix = glm::perspective(RADIANS(camAngle), window->props.aspectRatio, 0.01f, 200.0f);
		fastShotgunON = true;
	}

	if (key == GLFW_KEY_3) {
		renderHero = true;
		projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
		grenadeON = true;
	}
}

void Laborator5::OnKeyRelease(int key, int mods)
{
	// shotgun
	if (key == GLFW_KEY_1) {
		grenadeON = false;
		fastShotgunON = false;
	}

	// fast
	if (key == GLFW_KEY_2) {
		shotGunON = false;
		grenadeON = false;
	}

	// grenade
	if (key == GLFW_KEY_3) {
		shotGunON = false;
		fastShotgunON = false;
	}
}

void Laborator5::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		camera->RotateThirdPerson_OX(deltaY * sensivityOX);
		camera->RotateThirdPerson_OY(deltaX * sensivityOY);
		spikeTheHero.angle += sensivityOX * deltaX;
	}
}

void Laborator5::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		if (shotGunON == true && grenadeON == false && fastShotgunON == false) {
			gun gunObject;
			gunObject.angle = spikeTheHero.angle;
			gunObject.x = spikeTheHero.x;
			gunObject.y = spikeTheHero.y;
			gunObject.z = spikeTheHero.z;
			shotgun.push_back(gunObject);
		}

		if (fastShotgunON == true && grenadeON == false && shotGunON == false) {
			fastGun fastGunObject;
			fastGunObject.angle = spikeTheHero.angle;
			fastGunObject.x = spikeTheHero.x;
			fastGunObject.y = spikeTheHero.y;
			fastGunObject.z = spikeTheHero.z;
			fastShotgun.push_back(fastGunObject);
		}

		if (grenadeON == true && shotGunON == false && fastShotgunON == false) {
			grenade grenadeObject;
			grenadeObject.angle = spikeTheHero.angle;
			grenadeObject.x = spikeTheHero.x;
			grenadeObject.y = spikeTheHero.y;
			grenadeObject.z = spikeTheHero.z;
			grenadeBANG.push_back(grenadeObject);
		}
	}
}
