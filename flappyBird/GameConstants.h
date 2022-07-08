#pragma once

enum class Type {
	pipe = 0, score_collider, background
};

const int bird_start_x = 200;
const int bird_start_y = 350;

const int screen_width = 800;
const int screen_height = 600;

const int bird_width = 100;
const int bird_height = 80;

const int pipe_division = 300;
const int pipe_width = 100;
const int pipe_height = 400;

const int background_width = 576;
const int background_height = 600;

const double pipe_speed = 10.0;

const double impulse = 40;
const double cvelocity = -5.0;