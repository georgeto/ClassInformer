
// ****************************************************************************
// File: MainDialog.cpp
// Desc: Main Dialog
//
// ****************************************************************************
#include "stdafx.h"
#include "MainDialog.h"

#include <QtGui/QDialogButtonBox>


MainDialog::MainDialog(BOOL &optionPlaceStructs, BOOL &optionProcessStatic, BOOL &optionScanAllSegments, BOOL &optionOverwriteComments, BOOL &optionAudioOnDone) : QDialog(QApplication::activeWindow(), 0)
{
    // Required for static library resources
    Q_INIT_RESOURCE(QtResource);

    Ui::Dialog::setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    buttonBox->addButton("CONTINUE", QDialogButtonBox::AcceptRole);
    buttonBox->addButton("CANCEL", QDialogButtonBox::RejectRole);

    #define INITSTATE(obj,state) obj->setCheckState((state == TRUE) ? Qt::Checked : Qt::Unchecked);
    INITSTATE(checkBox1, optionPlaceStructs);
    INITSTATE(checkBox2, optionProcessStatic);
    INITSTATE(checkBox3, optionScanAllSegments);
    INITSTATE(checkBox4, optionOverwriteComments);
    INITSTATE(checkBox5, optionAudioOnDone);
    #undef INITSTATE

    // Apply style sheet
    QFile file(STYLE_PATH "style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text))
        setStyleSheet(QTextStream(&file).readAll());
}

// Do main dialog, return TRUE if canceled
BOOL doMainDialog(BOOL &optionPlaceStructs, BOOL &optionProcessStatic, BOOL &optionScanAllSegments, BOOL &optionOverwriteComments, BOOL &optionAudioOnDone)
{
	BOOL result = TRUE;
    MainDialog *dlg = new MainDialog(optionPlaceStructs, optionProcessStatic, optionScanAllSegments, optionOverwriteComments, optionAudioOnDone);
    if (dlg->exec())
    {
        #define CHECKSTATE(obj,var) var = dlg->obj->isChecked()
        CHECKSTATE(checkBox1, optionPlaceStructs);
        CHECKSTATE(checkBox2, optionProcessStatic);
        CHECKSTATE(checkBox3, optionScanAllSegments);
        CHECKSTATE(checkBox4, optionOverwriteComments);
        CHECKSTATE(checkBox5, optionAudioOnDone);
        #undef CHECKSTATE   
		result = FALSE;
    }	
	delete dlg; 
    return(result);	
}