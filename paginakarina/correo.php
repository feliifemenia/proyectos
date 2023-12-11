<?php
    $destinatario = 'felipefemenia20052604@gmail.com';
    //esto es al correo al que se enviara el mensaje

    $nombre = $_POST['nombre-apellido'];
    $email = $_POST['email'];
    $telefono = $_POST['telefono-de-contacto'];
    $mensaje = $_POST['mensaje'];

    $header = "Enviado desde la pagina";
    $mensajeCompleto = "Mi nombre es: " . $nombre;

    if (mail($destinatario, "Mensaje desde el formulario de contacto", $mensajeCompleto, $header)) {
        echo "<script>alert('Correo enviado');</script>";
    } else {
        echo "<script>alert('Error al enviar el correo');</script>";
    }
   
?>