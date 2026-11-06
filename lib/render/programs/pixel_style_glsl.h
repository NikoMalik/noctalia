#pragma once

#define NOCTALIA_PIXEL_STYLE_GLSL R"(
uniform float u_pixel;

float pixel_rect_distance(vec2 centered, vec2 half_size, float radius) {
    vec2 q = abs(centered) - half_size;
    float box = length(max(q, 0.0)) + min(max(q.x, q.y), 0.0);
    float steps = floor(radius / u_pixel + 0.5);
    vec2 c = -q;
    if (steps < 1.0 || c.x >= steps * u_pixel || c.y >= steps * u_pixel) {
        return box;
    }
    float stairs = 1e5;
    for (int i = 0; i <= 64; i++) {
        if (float(i) > steps) {
            break;
        }
        vec2 d = vec2(float(i), steps - float(i)) * u_pixel - c;
        stairs = min(stairs, length(max(d, 0.0)) + min(max(d.x, d.y), 0.0));
    }
    return max(box, stairs);
}

float pixel_corner_extent(float radius, float delta) {
    float steps = floor(radius / u_pixel + 0.5);
    float row = floor((radius - abs(delta)) / u_pixel);
    return clamp(radius - max(steps - row, 0.0) * u_pixel, 0.0, radius);
}

float pixel_shadow_level(float coverage) {
    return 0.5 * (step(0.15, coverage) + step(0.5, coverage));
}
)"
