
#ifndef __GLSettingsDialog_H__
#define __GLSettingsDialog_H__

//-------------------------------------------------------
// Class: GLSettingsDialog
//
// Description: Settings dialog thanks to Sander Jansen <sander@knology.net>
//-------------------------------------------------------
class GLSettingsDialog : public FXDialogBox
{
  FXDECLARE(GLSettingsDialog)

private:
  FXGLCanvas *canvas;
  FXFont     *thickfont;
  FXList     *extensionlist;

protected:
  GLSettingsDialog();
  void setup();

private:
  GLSettingsDialog(const FXDialogBox&);
  GLSettingsDialog &operator=(const FXDialogBox&);

public:
  long onCmdSave(FXObject*,FXSelector,void*);

public:
  enum {
    ID_SAVE = FXDialogBox::ID_LAST
    };

public:
  GLSettingsDialog(FXApp * app,FXGLCanvas*ca);
  GLSettingsDialog(FXWindow* owner,FXGLCanvas*ca);
  FXbool saveInformation(const FXString & filename);
  virtual ~GLSettingsDialog();
};

#endif
