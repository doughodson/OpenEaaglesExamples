
#ifndef __SettingsDialog_H__
#define __SettingsDialog_H__

#include "fx.h"

//-------------------------------------------------------
// Class: SettingsDialog
//
// Description: Settings dialog thanks to Sander Jansen <sander@knology.net>
//-------------------------------------------------------
class SettingsDialog : public FXDialogBox
{
   FXDECLARE(SettingsDialog)

private:
   FXGLCanvas* canvas;
   FXFont* thickfont;
   FXList* extensionlist;

protected:
   SettingsDialog();
   void setup();

private:
   SettingsDialog(const FXDialogBox&);
   SettingsDialog &operator=(const FXDialogBox&);

public:
   long onCmdSave(FXObject*, FXSelector, void*);

public:
   enum {
      ID_SAVE = FXDialogBox::ID_LAST
   };

public:
   SettingsDialog(FXApp* app, FXGLCanvas* ca);
   SettingsDialog(FXWindow* owner, FXGLCanvas* ca);
   FXbool saveInformation(const FXString& filename);
   virtual ~SettingsDialog();
};

#endif
