#include "Hero.h"
//! default constructor -> no pass in argument/parameter
Hero::Hero(){
	health = 100;
	level = 1;
	damage = 10;
}
Hero::Hero(int h, int l, int d){
	health = h;
	level = l;
	damage = d;
}
void Hero::SetHealth(int h){
	health -= h;
}
void Hero::SetLevel(int l){
	level = l;
}
void Hero::SetDamage(int d){
	damage = d;
}
int Hero::GetHealth(){
	return health;
}
int Hero::GetLevel(){
	return level;
}
int Hero::GetDamage(){
	return damage;
}
void Hero::Attack(Hero h){
	SetHealth(h.damage);
}
