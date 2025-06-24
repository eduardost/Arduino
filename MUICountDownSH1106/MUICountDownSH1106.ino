/*

  MUICountDown.ino

  https://github.com/olikraus/u8g2/wiki/muimanual#muicountdown-example
  
  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2021, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

*/

#include <Arduino.h>
#include <U8g2lib.h>
#include <MUIU8g2.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// Please UNCOMMENT one of the contructor lines below
// U8g2 Contructor List (Picture Loop Page Buffer)
// The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
// Please update the pin numbers according to your setup. Use U8X8_PIN_NONE if the reset pin is not connected
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
// End of constructor list


MUIU8G2 mui;

/*
  global variables which form the communication gateway between the user interface and the rest of the code
*/
uint8_t number_input = 2;       // variable where the user can input a number between 0 and 9
uint8_t exit_code = 0;                  // return value from the menu system

/* 
  MUIF table: Each entry defines a field, which can be used in FDS to describe a form.
*/


muif_t muif_list[] = {
  /* normal text style */
  MUIF_U8G2_FONT_STYLE(0, u8g2_font_helvR08_tr),
  
  /* Leave the menu system */
  MUIF_VARIABLE("LV",&exit_code,mui_u8g2_btn_exit_wm_fi),
  
  /* input for a number between 0 to 9 */
  MUIF_U8G2_U8_MIN_MAX("IN", &number_input, 0, 9, mui_u8g2_u8_min_max_wm_mse_pi),
  
  /* MUI_LABEL is used to place fixed text on the screeen */
  MUIF_LABEL(mui_u8g2_draw_text)
};

/*
  The form definition string (fds) defines all forms and the fields on those forms.
  A new form always starts with MUI_FORM(u). The form ends with the next MUI_FORM() or the end of the fds.
  Inside the form use fields or the style command (MUI_STYLE)
  The fields are placed on the form with
    MUI_XY(id, x, y)                     Field 'id' without extra argument or text placed at the specified xy position
    MUI_XYT(id, x, y, text)            Field 'id' with the specified test at position xy
    MUI_XYA(id, x, y, a)                 Field 'id' with argument 'a' at position xy
    MUI_XYAT(id, x, y, a, text)         Field 'id' with argument and text placed at position xy
    MUI_LABEL(x, y, text)                 Place "text" on the form. Can be used only if "MUIF_LABEL(mui_u8g2_draw_text)" is available in MUIF table.

*/


fds_t fds_data[] MUI_PROGMEM = 
MUI_FORM(1)
MUI_STYLE(0)
MUI_LABEL(5,12, "Countdown Time")
MUI_LABEL(5,30, "Seconds:")
MUI_XY("IN",60, 30)
MUI_XYT("LV",64, 59, " OK ")
;


void setup(void) {

  // U8g2 SH1106 Proto-Shield
  //u8g2.begin(/* menu_select_pin= */ 2, /* menu_next_pin= */ 4, /* menu_prev_pin= */ 7, /* menu_up_pin= */ 6, /* menu_down_pin= */ 5, /* menu_home_pin= */ 3);
  
  // U8g2 SH1106 MUI Test Shield
  u8g2.begin(/* menu_select_pin= */ 6, /* menu_next_pin= */ 7, /* menu_prev_pin= */ 5, /* menu_up_pin= */ U8X8_PIN_NONE, /* menu_down_pin= */ U8X8_PIN_NONE, /* menu_home_pin= */ U8X8_PIN_NONE);

  // DOGS102 Shield (http://shieldlist.org/controlconnection/dogs102)
  //u8g2.begin(/* menu_select_pin= */ 5, /* menu_next_pin= */ 4, /* menu_prev_pin= */ 2, /* menu_up_pin= */ U8X8_PIN_NONE, /* menu_down_pin= */ U8X8_PIN_NONE, /* menu_home_pin= */ 3);
  
  // DOGM128 Shield (http://shieldlist.org/schmelle2/dogm128) + DOGXL160 Shield
  //u8g2.begin(/* menu_select_pin= */ 2, /* menu_next_pin= */ 3, /* menu_prev_pin= */ 7, /* menu_up_pin= */ U8X8_PIN_NONE, /* menu_down_pin= */ U8X8_PIN_NONE, /* menu_home_pin= */ 8);
  
  // MKR Zero Test Board
  // u8g2.begin(/*Select=*/ 0, /*Right/Next=*/ 1, /*Left/Prev=*/ 2, /*Up=*/ 4, /*Down=*/ 3, /*Home/Cancel=*/ A6); 

  // Arduboy
  //u8g2.begin(/*Select=*/ A0, /*Right/Next=*/ 5, /*Left/Prev=*/ 9, /*Up=*/ 8, /*Down=*/ 10, /*Home/Cancel=*/ A1); // Arduboy DevKit
  //u8g2.begin(/*Select=*/ 7, /*Right/Next=*/ A1, /*Left/Prev=*/ A2, /*Up=*/ A0, /*Down=*/ A3, /*Home/Cancel=*/ 8); // Arduboy 10 (Production)
  
  
  mui.begin(u8g2, fds_data, muif_list, sizeof(muif_list)/sizeof(muif_t));
  mui.gotoForm(/* form_id= */ 1, /* initial_cursor_position= */ 0);
}


uint8_t is_redraw = 1;
long milliseconds = 0;

void loop(void) {

  /* check whether the menu is active */
  if ( mui.isFormActive() ) {

    /* if so, then draw the menu */
    if ( is_redraw ) {
      u8g2.firstPage();
      do {
          mui.draw();
      } while( u8g2.nextPage() );
      is_redraw = 0;
    }
    
    /* handle events */
    switch(u8g2.getMenuEvent()) {
      case U8X8_MSG_GPIO_MENU_SELECT:
        mui.sendSelect();
        is_redraw = 1;
        break;
      case U8X8_MSG_GPIO_MENU_NEXT:
        mui.nextField();
        is_redraw = 1;
        break;
      case U8X8_MSG_GPIO_MENU_PREV:
        mui.prevField();
        is_redraw = 1;
        break;
    }
    
    /* did the user deactivate the menu? If so, start the countdown */
    
    if ( mui.isFormActive() )
      milliseconds = ((long)number_input) * 1000;
      
  } else {
  
    /* menu not active: show countdown */
    
    if ( milliseconds <= 0 ) {
      /* countdown reached 0: activate menu again */
      /* The exit button has stored its location: restoreForm will */
      /* activate MUI and will put focus on the ok button */
      mui.restoreForm();        
    } else {
      /* execute countdown */
      u8g2.setFont(u8g2_font_helvR08_tr);
      u8g2.firstPage();
      do {
          u8g2.setCursor(0,20);
          u8g2.print(milliseconds);
      } while( u8g2.nextPage() );
      milliseconds -= 100;
      delay(100);
    }
  }
}


