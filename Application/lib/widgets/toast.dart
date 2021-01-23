// Import the material design widgets
import "package:flutter/material.dart";

// Import fluttertoast package
import 'package:fluttertoast/fluttertoast.dart';

//::postToast::(message to show)
//  Creates a toast, a short lived message, at the bottom of the screen showing the message
//  Wrapper around the fluttertoast.showToast method
void postToast(String message) {
  Fluttertoast.showToast(
      msg: message,
      toastLength: Toast.LENGTH_SHORT,
      gravity: ToastGravity.BOTTOM,
      timeInSecForIosWeb: 1,
      backgroundColor: Colors.grey[600],
      textColor: Colors.white,
      fontSize: 16.0);
}
