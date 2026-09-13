#ifndef W3DOWNLOADDIALOG_H
#define W3DOWNLOADDIALOG_H

#include <QDialog>

class QLabel;
class QProgressBar;
class QPushButton;

// Modal progress dialog for the W3 download -> extract -> quick patch flow.
// It can't be dismissed by the user: Esc, the close button and Cancel only
// request cancellation, and only while the current stage allows it.
class W3DownloadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit W3DownloadDialog(QWidget *parent = nullptr);

    // Switches to a new stage. The bar is indeterminate until the first setProgress().
    void setStage(const QString &text, bool cancellable);
    void finish();

public slots:
    void setProgress(int percent);

signals:
    void cancelRequested();

protected:
    void reject() override;

private:
    QLabel *label;
    QProgressBar *bar;
    QPushButton *cancelButton;
    bool cancellable = false;
    bool finishing = false;
};

#endif // W3DOWNLOADDIALOG_H
