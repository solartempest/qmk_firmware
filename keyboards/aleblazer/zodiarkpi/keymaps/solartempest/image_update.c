#ifdef QUANTUM_PAINTER_ENABLE
#include "images/ZodiarkPiLogoSTpink.qgf.c"
#include "images/jelly1.qgf.c"
#include "images/jelly2.qgf.c"

/*
Code for defining displays
*/


static painter_image_handle_t image_layer_0;
static painter_image_handle_t image_layer_1;
static painter_image_handle_t image_layer_2;


void update_display_for_layer(uint8_t layer) {
    // Example: Draw an image corresponding to the layer
    switch (layer) {
        case 0:
			if (is_keyboard_left()) {
                qp_drawimage(display,0,0,image_layer_0);
            }
            break;
        case 1:
            if (is_keyboard_left()) {
                qp_drawimage(display,0,0,image_layer_0);
            }
            break;
        case 2:
            if (is_keyboard_left()) {
                qp_drawimage(display,0,0,image_layer_0);
            }
            break;
		case 3:
            if (is_keyboard_left()) {
                qp_drawimage(display,0,0,image_layer_2);
            }
            break;
        // Add more cases for additional layers
        default:
            if (is_keyboard_left()) {
				image = qp_load_image_mem(gfx_ZodiarkPiLogoSTpink);
			}
            break;
    }
}


layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state); // Get the current active layer

    // Update the display based on the current layer
    update_display_for_layer(layer);

    return state;
}

void keyboard_post_init_kb(void)
{
    debug_enable=true;
    defer_exec(3000, deferred_init, NULL);
    image_layer_0 = qp_load_image_mem(gfx_ZodiarkPiLogoSTpink);
    image_layer_1 = qp_load_image_mem(gfx_jelly1);
    image_layer_2 = qp_load_image_mem(gfx_jelly2);
}
#endif