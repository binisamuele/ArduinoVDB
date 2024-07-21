#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String longText = "Tra due alberi sono appesa, dondolando faccio resa. Se vuoi rilassarti, sai, su di me riposerai.";
int textLength;
int scrollPosition = 0;

void setup() {
  // Set up the LCD's number of columns and rows (16x2 LCD in this case)
  lcd.begin(16, 2);
  lcd.clear();

  // Set the text length
  textLength = longText.length();
}

void loop() {
  // Set the cursor to the beginning of the first line
  lcd.setCursor(0, 0);

  // Print the substring of the long text based on the scroll position
  lcd.print(longText.substring(scrollPosition, scrollPosition + 16));

  // Update the scroll position
  scrollPosition++;

  // If we've scrolled past the end of the text, reset the scroll position
  if (scrollPosition > textLength - 16) {
    scrollPosition = 0;
  }

  // Wait for a short period before scrolling again
  delay(250);
}