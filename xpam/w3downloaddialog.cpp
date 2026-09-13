#include "w3downloaddialog.h"
#include "QLabel"
#include "QProgressBar"
#include "QPushButton"
#include "QVBoxLayout"
#include "QHBoxLayout"

W3DownloadDialog::W3DownloadDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Installing Warcraft III");
    setWindowModality(Qt::ApplicationModal);
    setMinimumWidth(420);

    label = new QLabel(this);
    label->setWordWrap(true);

    bar = new QProgressBar(this);

    cancelButton = new QPushButton("Cancel", this);
    connect(cancelButton, &QPushButton::clicked, this, &W3DownloadDialog::reject);

    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addStretch();
    buttons->addWidget(cancelButton);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(bar);
    layout->addLayout(buttons);
}

void W3DownloadDialog::setStage(const QString &text, bool cancellable)
{
    this->cancellable = cancellable;
    label->setText(text);
    bar->setRange(0, 0);
    cancelButton->setEnabled(cancellable);
}

void W3DownloadDialog::setProgress(int percent)
{
    if (bar->maximum() == 0) {
        bar->setRange(0, 100);
    }
    bar->setValue(percent);
}

void W3DownloadDialog::finish()
{
    finishing = true;
    accept();
}

void W3DownloadDialog::reject()
{
    if (finishing) {
        QDialog::reject();
        return;
    }
    if (!cancellable) return;

    cancellable = false;
    cancelButton->setEnabled(false);
    label->setText("Cancelling...");
    emit cancelRequested();
}
