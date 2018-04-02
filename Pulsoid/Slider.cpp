#pragma once
#include "header.h"
#include "Slider.h"

Slider::Slider()
	: _value(0)
{
	_outline.setFillColor(sf::Color::White);
	_outline.setSize(sf::Vector2f(200, 4));
	_center.setFillColor(sf::Color::Black);
	_center.setOutlineColor(sf::Color::White);
	_center.setOutlineThickness(4);
	_center.setSize(sf::Vector2f(4, 10));
}
void Slider::setPosition(sf::Vector2f & position)
{
	_outline.setPosition(position);
	_center.setPosition(sf::Vector2f(position.x + 3 + _value, position.y - 3));
}
void Slider::operator++()
{
	if (_value < 100)
	{
		_value++;
		_center.move(2, 0);
	}
}
void Slider::operator--()
{
	if (_value > 0)
	{
		_value--;
		_center.move(-2, 0);
	}
}
void Slider::operator+(int val)
{
	if (_value < 100)
	{
		_value += val;
		_center.move(2.f * val, 0);
	}
}
void Slider::operator-(int val)
{
	if (_value > 0)
	{
		_value -= val;
		_center.move(-2.f * val, 0);
	}
}
int Slider::getValue()
{
	return _value;
}
void Slider::setValue(int val)
{
	_value = val;
	_center.setPosition(sf::Vector2f(_outline.getPosition().x + 3 + (2 * _value), _outline.getPosition().y - 3));
}
void Slider::draw(sf::RenderWindow & window)
{
	window.draw(_outline);
	window.draw(_center);
}
