//
//
// "Trash" configuration
//
// (c) David Faure 2000

#include <qlabel.h>
#include <qbuttongroup.h>
#include <qlayout.h>
#include <qcheckbox.h>
#include <qradiobutton.h>
#include <qwhatsthis.h>

#include "trashopts.h"

#include <kapp.h>
#include <kdialog.h>
#include <konqdefaults.h> // include default values directly from libkonq
#include <klocale.h>
#include <kconfig.h>

//-----------------------------------------------------------------------------

KTrashOptions::KTrashOptions(KConfig *config, QString group, QWidget *parent, const char *name )
    : KCModule( parent, name ), g_pConfig(config), groupname(group)
{
    QGridLayout *lay = new QGridLayout(this, 3, 2,
                                       KDialog::marginHint(),
                                       KDialog::spacingHint());
    lay->setRowStretch(2,1); // last row
    lay->setColStretch(1,1); // last col

    QButtonGroup *bg = new QButtonGroup( i18n("On delete:"), this );
    QVBoxLayout *bgLay = new QVBoxLayout(bg, KDialog::marginHint(),
				       KDialog::spacingHint());
    bg->setExclusive( TRUE );

    QWhatsThis::add( bg, i18n("This option tells Konqueror what to do"
       " by default when you \"delete\" a file."
       " <ul><li><em>Move To Trash:</em> moves the file to your trash directory,"
       " from where it can be recovered very easily.</li>"
       " <li><em>Delete:</em> simply deletes the file.</li>"
       " <li><em>Shred:</em> not only deletes the file, but overwrites"
       " the area on the disk where the file is stored, making recovery impossible."
       " You should only use this method as the default if you routinely work with"
       " very confidential information.</li></ul>") );

    connect(bg, SIGNAL( clicked( int ) ), SLOT( changed() ));
    connect(bg, SIGNAL( clicked( int ) ), SLOT( slotDeleteBehaviourChanged( int ) ));

    bgLay->addSpacing(10);

    rbMoveToTrash = new QRadioButton( i18n("Move To Trash"), bg );
    bgLay->addWidget(rbMoveToTrash);

    rbDelete = new QRadioButton( i18n("Delete"), bg );
    bgLay->addWidget(rbDelete);

    rbShred = new QRadioButton( i18n("Shred"), bg );
    bgLay->addWidget(rbShred);

    lay->addWidget(bg, 0, 0);

    m_pConfirmDestructive = new QCheckBox(i18n("Confirm destructive actions"),
					  this);
    connect(m_pConfirmDestructive, SIGNAL(clicked()), this, SLOT(changed()));
    lay->addWidget(m_pConfirmDestructive, 1, 0);

    QWhatsThis::add( m_pConfirmDestructive, i18n("If you uncheck this option,"
       " Konqueror will not ask you for confirmation before deleting a file."
       " If the file is not in your trash directory, recovery may not be"
       " possible, so be careful!") );

    load();
}

void KTrashOptions::load()
{
    // *** load and apply to GUI ***
    g_pConfig->setGroup( groupname );
    deleteAction = g_pConfig->readNumEntry("DeleteAction", DEFAULT_DELETEACTION);
    rbMoveToTrash->setChecked( deleteAction == 1 );
    rbDelete->setChecked( deleteAction == 2 );
    rbShred->setChecked( deleteAction == 3 );
    m_pConfirmDestructive->setChecked(g_pConfig->readBoolEntry("ConfirmDestructive", true));
}

void KTrashOptions::defaults()
{
    rbMoveToTrash->setChecked( DEFAULT_DELETEACTION == 1 );
    rbDelete->setChecked( DEFAULT_DELETEACTION == 2 );
    rbShred->setChecked( DEFAULT_DELETEACTION == 3 );
    m_pConfirmDestructive->setChecked(true);
}

void KTrashOptions::save()
{
    g_pConfig->setGroup( groupname );
    g_pConfig->writeEntry( "DeleteAction", deleteAction );
    g_pConfig->writeEntry( "ConfirmDestructive", m_pConfirmDestructive->isChecked());
    g_pConfig->sync();
}

QString KTrashOptions::quickHelp()
{
    return i18n("<h1>Trash Options</h1> Here you can modify the behaviour"
                "of konqueror when you want to delete a file."
                "<h2>On delete:</h2>This option determines what konqueror"
                "will do with a file you chose to delete (e.g. in a context menu).<ul>"
                "<li><em>Move To Trash</em> will move the file to the trash folder,"
                "instead of deleting it, so you can easily recover it.</li>"
                "<li><em>Delete</em> will simply delete the file.</li>"
                "<li><em>Shred</em> will not only delete the file, but will first"
                "overwrite it with different bit patterns. This makes recovery impossible."
                "Use it, if you're keeping very sensitive data."
                "<h2>Confirm destructive actions</h2>Check this box if you want konqueror"
                "to ask \"Are you sure?\" before doing any destructive action (e.g. delete or shred).");
}

void KTrashOptions::slotDeleteBehaviourChanged( int b )
{
    deleteAction = b + 1;
}

void KTrashOptions::changed()
{
    emit KCModule::changed(true);
}

#include "trashopts.moc"
