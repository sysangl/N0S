#include "screen.h"
#include "timer.h"
#include "math.h"
#define screen_width 80
#define screen_height 25
#define theta_spacing 0.07f
#define phi_spacing   0.02f
#define R1 1.0f
#define R2 2.0f
#define K2 5.0f
#define K1 (screen_width * K2 * 3.0f / (8.0f * (R1 + R2)))
char output[screen_width][screen_height];
float zbuffer[screen_width][screen_height];
float g_costheta, g_sintheta, g_cosphi, g_sinphi;
float g_circlex, g_circley, g_x, g_y, g_z, g_ooz, g_L;
int g_xp, g_yp;
float g_cosA, g_sinA, g_cosB, g_sinB;
float g_cos_theta, g_sin_theta, g_cos_phi, g_sin_phi;
float g_cos_dtheta, g_sin_dtheta, g_cos_dphi, g_sin_dphi;
float g_new_cos_phi, g_new_sin_phi, g_new_cos_theta, g_new_sin_theta;
float g_xf, g_yf;
int g_ti, g_pi, g_lum;
int g_theta_steps, g_phi_steps;
int g_i, g_j;
char *g_vidmem;
float a,b;
void k_donut() {
    __asm__ volatile ("cli");
    k_putchar('1', 78, 0);

    a += 0.07;
    b += 0.03;
    g_cosA = cos(a); g_sinA = sin(a);
    g_cosB = cos(b); g_sinB = sin(b);
    k_putchar('2', 78, 0);

    for (g_i = 0; g_i < screen_width; g_i++)
        for (g_j = 0; g_j < screen_height; g_j++) {
            output[g_i][g_j] = ' ';
            zbuffer[g_i][g_j] = 0.0;
        }
    k_putchar('3', 78, 0);

    g_cos_dtheta = cos(theta_spacing);
    g_sin_dtheta = sin(theta_spacing);
    g_cos_dphi   = cos(phi_spacing);
    g_sin_dphi   = sin(phi_spacing);


    g_cos_theta = 1.0; g_sin_theta = 0.0;
    g_theta_steps = (int)(2*PI / theta_spacing) + 1;
    g_phi_steps   = (int)(2*PI / phi_spacing)   + 1;

for (g_ti = 0; g_ti < g_theta_steps; g_ti++) {
        g_cos_phi = 1.0; g_sin_phi = 0.0;
        for (g_pi = 0; g_pi < g_phi_steps; g_pi++) {
            g_circlex = R2 + R1*g_cos_theta;
            g_circley = R1*g_sin_theta;
            g_x = g_circlex*(g_cosB*g_cos_phi + g_sinA*g_sinB*g_sin_phi) - g_circley*g_cosA*g_sinB;
            g_y = g_circlex*(g_sinB*g_cos_phi - g_sinA*g_cosB*g_sin_phi) + g_circley*g_cosA*g_cosB;
            g_z = K2 + g_cosA*g_circlex*g_sin_phi + g_circley*g_sinA;

            if (g_z > 0) {
                g_ooz = 1/g_z;
                g_xf = screen_width/2  + K1*g_ooz*g_x;
                g_yf = screen_height/2 - K1*g_ooz*g_y;
                if (g_xf < 0) g_xf = 0;
                if (g_xf >= screen_width)  g_xf = screen_width - 1;
                if (g_yf < 0) g_yf = 0;
                if (g_yf >= screen_height) g_yf = screen_height - 1;
				
                g_xp = (int)g_xf;
                g_yp = (int)g_yf;
				
                g_L = g_cos_phi*g_cos_theta*g_sinB - g_cosA*g_cos_theta*g_sin_phi -
                    g_sinA*g_sin_theta + g_cosB*(g_cosA*g_sin_theta - g_cos_theta*g_sinA*g_sin_phi);
					
                if (g_L > 0 && g_ooz > zbuffer[g_xp][g_yp]) {
                    zbuffer[g_xp][g_yp] = g_ooz;
                    g_lum = (int)(g_L * 8);
                    if (g_lum > 11) g_lum = 11;
                    output[g_xp][g_yp] = ".,-~:;=!*#$@"[g_lum];
                }
				
            }
            g_new_cos_phi = g_cos_phi*g_cos_dphi - g_sin_phi*g_sin_dphi;
            g_new_sin_phi = g_sin_phi*g_cos_dphi + g_cos_phi*g_sin_dphi;
            g_cos_phi = g_new_cos_phi;
            g_sin_phi = g_new_sin_phi;
			
        }
        g_new_cos_theta = g_cos_theta*g_cos_dtheta - g_sin_theta*g_sin_dtheta;
        g_new_sin_theta = g_sin_theta*g_cos_dtheta + g_cos_theta*g_sin_dtheta;
        g_cos_theta = g_new_cos_theta;
        g_sin_theta = g_new_sin_theta;
    }
    k_putchar('5', 78, 0);

	g_vidmem = (char *) 0xb8000;
		for (g_j = 0; g_j < screen_height; g_j++)
			for (g_i = 0; g_i < screen_width; g_i++) {
				g_vidmem[(g_j*80+g_i)*2]     = output[g_i][g_j];
				g_vidmem[(g_j*80+g_i)*2 + 1] = WHITE_TXT;
			}
		k_putchar('6', 78, 0);

		__asm__ volatile ("sti");

}