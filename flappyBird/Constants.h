#pragma once

enum class Side {
	left = 0, right, up, down
};

enum class Type {
	pipe = 0, score_collider
};

const double UPDATE_RATE = 32;
