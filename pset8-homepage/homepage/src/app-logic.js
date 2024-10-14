

document.addEventListener ('DOMContentLoaded', function()
{
    // Contact Page: Submit button --> Toast Trigger
    const submitBtn = document.getElementById('submitBtn');
    const submitToast = document.getElementById('submitMsg');

    const emailForm = document.getElementById('emailForm');
    const messageForm = document.getElementById('messageForm');
    
    if (submitBtn) {
      const submitConfirm = bootstrap.Toast.getOrCreateInstance(submitToast)
      submitBtn.addEventListener('click', () => {
        emailForm.value = "";
        messageForm.value = "";
        submitConfirm.show()
      });

    };
    
});
