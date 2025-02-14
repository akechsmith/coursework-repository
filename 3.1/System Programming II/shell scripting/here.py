# views.py

from django.http import JsonResponse
from django.core.mail import send_mail

def send_bin_status_notification(request, bin_status):
    """
    View to send notifications when the bin is full.

    Args:
        request (HttpRequest): The HTTP request object.
        bin_status (str): Status of the bin ('Full' or 'Empty').

    Returns:
        JsonResponse: Success message.
    """
    if bin_status == 'Full':
        # Example: Send email notification
        send_mail(
            'Waste Bin Full Notification',
            'A waste bin is full and needs to be emptied.',
            'system@example.com',  # From email
            ['recipient@example.com'],  # To email
            fail_silently=False,
        )

        # You can add additional notification methods here (e.g., SMS, push notifications)

    return JsonResponse({'message': 'Notification sent successfully.'})

# urls.py

from django.urls import path
from . import views

urlpatterns = [
    path('send-notification/<str:bin_status>/', views.send_bin_status_notification, name='send_notification'),
]

