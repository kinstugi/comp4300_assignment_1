#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>

struct Entity {
	std::shared_ptr<sf::Shape> m_shape;
	float m_speed[2] = { 0.0f, 0.0f };
	std::string m_name;
	bool m_isVisible;
	float m_color[3] = { 0.0f, 0.0f, 0.0f };

	Entity(
		std::shared_ptr<sf::Shape> shape, 
		std::string name = ""
	) : m_shape(shape), m_name(name), m_isVisible(true)
	{}
};

void moveShape(sf::Shape& shape, float speed[], unsigned int screenWidth, unsigned int screenHeight);
int isOutOfBounds(const sf::Shape& shape, unsigned int screenWidth, unsigned int screenHeight);
void loadEnities(std::vector<Entity> &entities,  unsigned int &screenWidth, unsigned int &screenHeight);

int main()
{
	//imgui menu
	bool selectedShapeVisible = true;
	int selectedShapeIndex = 0;
	std::vector<const char*> shapeNames;
	shapeNames.reserve(10);
	int radius = 0, width = 0, height = 0, sz[2] = { 1, 1 };

	unsigned int screenWidth = 400, screenHeight = 400; 
	std::vector<Entity> entities;
	loadEnities(entities, screenWidth, screenHeight);

	sf::RenderWindow window(sf::VideoMode({ screenWidth, screenHeight }), "assignment one");
	if (!ImGui::SFML::Init(window)) return  -1;

	for (auto& entity : entities)
		shapeNames.push_back(entity.m_name.data());

	sf::Clock deltaTimer;
	while (window.isOpen())
	{
		while (const auto event = window.pollEvent())
		{
			if (event.has_value())
				ImGui::SFML::ProcessEvent(window, event.value());
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
		
		ImGui::SFML::Update(window, deltaTimer.restart());

		//sfml menu
		ImGui::Begin("Properties");
		ImGui::Combo("Shapes", &selectedShapeIndex, shapeNames.data(), shapeNames.size());
		ImGui::Checkbox("IsVisible", &(entities[selectedShapeIndex].m_isVisible));
		ImGui::ColorEdit3("Color", entities[selectedShapeIndex].m_color);
		ImGui::SliderFloat2("Speed", entities[selectedShapeIndex].m_speed, -1.0f, 1.0f, "%.2f");
		if (entities[selectedShapeIndex].m_name[0] == 'C')
			ImGui::SliderInt("Radius", &radius, 1, 100);
		else
			ImGui::SliderInt2("Size", sz, 1, 100);
		ImGui::End();

		//apply color change
		entities[selectedShapeIndex].m_shape->setFillColor(
			sf::Color(entities[selectedShapeIndex].m_color[0], entities[selectedShapeIndex].m_color[1], entities[selectedShapeIndex].m_color[2])
		);
		
		for(auto &entity: entities)
			moveShape(*(entity.m_shape), entity.m_speed, screenWidth, screenHeight);

		window.clear();
		for (auto& e : entities)
		{
			if (e.m_isVisible)
				window.draw(*(e.m_shape));
		}
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}

void moveShape(sf::Shape& shape, float speed[], unsigned int screenWidth, unsigned int screenHeight)
{
	shape.setPosition({ shape.getPosition().x + speed[0] , shape.getPosition().y + speed[1]});
	
	int bounceState = isOutOfBounds(shape, screenWidth, screenWidth);
	if (bounceState & 1 || bounceState & 2)
		speed[0] *= -1;
	if (bounceState & 4 || bounceState & 8)
		speed[1] *= -1;
}

int isOutOfBounds(const sf::Shape& shape, unsigned int screenWidth, unsigned int screenHeight)
{
	float pos_x = shape.getGlobalBounds().position.x;
	float pos_y = shape.getGlobalBounds().position.y;
	float width = shape.getGlobalBounds().size.x;
	float height = shape.getGlobalBounds().size.y;

	int res = 0;
	if (pos_x <= 0)
		res |= 1;
	if (pos_x + width >= screenWidth)
		res |= 2;
	if (pos_y <= 0)
		res |= 4;
	if (pos_y + height >= screenHeight)
		res |= 8;
	return res;
}

void loadEnities(std::vector<Entity>& entities, unsigned int& screenWidth, unsigned int& screenHeight)
{
	std::string tag;
	float pos_x, pos_y; 
	float speed_x, speed_y;
	int width, height, radius, fontSize;
	int colorR, colorG, colorB;
	char ch;
	int sW, sH;

	std::ifstream fin("config.txt");

	while (fin >> tag)
	{
		if (tag == "Window")
		{
			fin >> sW >> sH;
			screenWidth = sW; screenHeight = sH;
		}
		else if (tag == "Font")
		{
			std::string name;
			fin >> name >> fontSize >> colorR >> colorG >> colorB;
		}
		else if (tag == "Circle")
		{
			std::string name;
			fin >> name >> pos_x >> pos_y >> speed_x >> speed_y >> colorR >> colorG >> colorB >> radius;
			Entity circleEntity(std::make_shared<sf::CircleShape>(radius),  name);
			circleEntity.m_shape->setFillColor(sf::Color(colorR, colorG, colorB));
			circleEntity.m_color[0] = colorR; circleEntity.m_color[1] = colorG; circleEntity.m_color[2] = colorB;
			circleEntity.m_shape->setPosition(sf::Vector2f(pos_x, pos_y));
			circleEntity.m_speed[0] = speed_x; circleEntity.m_speed[1] = speed_y;
			entities.push_back(circleEntity);
		}
		else if (tag == "Rectangle")
		{
			std::string name;
			fin >> name >> pos_x >> pos_y >> speed_x >> speed_y >> colorR >> colorG >> colorB >> width >> height;
			Entity rec(std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height)), name);
			rec.m_shape->setFillColor(sf::Color(colorR, colorG, colorB));
			rec.m_shape->setPosition(sf::Vector2f(pos_x, pos_y));
			rec.m_color[0] = colorR; rec.m_color[1] = colorG; rec.m_color[2] = colorB;
			rec.m_speed[0] = speed_x; rec.m_speed[1] = speed_y;
			entities.push_back(rec);
		}
	}
}