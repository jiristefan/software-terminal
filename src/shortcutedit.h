#ifndef HOTKEYEDIT_H
#define HOTKEYEDIT_H

#include "macros.h"

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>

class ShortcutEdit : public QLineEdit
{
    Q_OBJECT
public:
    ShortcutEdit(QWidget* parent = nullptr);

private:
    int getModifier(QKeyEvent* e);
    QKeySequence key_sequence;

signals:
    void shortcutSet(QKeySequence key_sequence);

protected:
    void keyPressEvent(QKeyEvent* e) override;
    void focusInEvent(QFocusEvent* e) override;
    void focusOutEvent(QFocusEvent* e) override;
};

#endif // HOTKEYEDIT_H
