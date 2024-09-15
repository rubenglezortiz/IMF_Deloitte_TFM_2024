#pragma once
#include <iostream>
#include <functional>

enum ShaderType { nullSh, AttackSh, DefenseSh, HealingSh, KirinSh, DruidaSh };
enum ShaderForm { Cross, TxT, VikingForm, ShaderWolf };

enum selectorColor { selector, selectorA, selectorH };

class Ability;

class AbilityStruct
{
public:
	//using AbilityStructFunction = void(int x, int y, AbilityStruct* father);
	AbilityStruct(selectorColor selector, ShaderForm form, ShaderType type, int distance = 1);
	AbilityStruct() :self(nullptr) {}
	selectorColor selector;
	ShaderForm  shaderForm;
	ShaderType shaderType;
	int distance;
	
	Ability* getAbility();
	virtual void OnDie();
	virtual void initiliceData(Ability* ab);
	virtual bool AbilityExecute(int x, int y);
	virtual void finTurno();
	virtual void OnCross() {};
protected:
	Ability* self;
};

