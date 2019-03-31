#pragma once
#include <SFML/Graphics.hpp>
#include "gate.h"
class andGate : public gate {
private:

	//quite a lot of these are already inacsessable, they are just here for my memory
	using::gate::AttacherPos;
	using::gate::checkRotation;
	using::gate::drag;
	using::gate::filelocation;
	using::gate::hb;
	using::gate::loadTexture;
	using::gate::rotationAmount;
	using::gate::scale;
	using::gate::sprite;
	using::gate::texture;
public:
	virtual void calc();
	virtual ~andGate();
	andGate();
};
class notGate :public gate {
private:
	//quite a lot of these are already inacsessable, they are just here for my memory
	using::gate::AttacherPos;
	using::gate::checkRotation;
	using::gate::drag;
	using::gate::filelocation;
	using::gate::hb;
	using::gate::loadTexture;
	using::gate::rotationAmount;
	using::gate::scale;
	using::gate::sprite;
	using::gate::texture;
public:
	void calc();
	~notGate();
	notGate();
};
class orGate : public gate {
private:
	//quite a lot of these are already inacsessable, they are just here for my memory
	using::gate::AttacherPos;
	using::gate::checkRotation;
	using::gate::drag;
	using::gate::filelocation;
	using::gate::hb;
	using::gate::loadTexture;
	using::gate::rotationAmount;
	using::gate::scale;
	using::gate::sprite;
	using::gate::texture;
public:
	void calc();
	~orGate();
	orGate();
};
class xOrGate : public gate {
private:
	//quite a lot of these are already inacsessable, they are just here for my memory
	using::gate::AttacherPos;
	using::gate::checkRotation;
	using::gate::drag;
	using::gate::filelocation;
	using::gate::hb;
	using::gate::loadTexture;
	using::gate::rotationAmount;
	using::gate::scale;
	using::gate::sprite;
	using::gate::texture;
public:
	void calc();
	~xOrGate();
	xOrGate();
};
class splitterGate :public gate {
private:
	//quite a lot of these are already inacsessable, they are just here for my memory
	using::gate::AttacherPos;
	using::gate::checkRotation;
	using::gate::drag;
	using::gate::filelocation;
	using::gate::hb;
	using::gate::loadTexture;
	using::gate::rotationAmount;
	using::gate::scale;
	using::gate::sprite;
	using::gate::texture;
public:
	void calc();
	~splitterGate();
	splitterGate();
};