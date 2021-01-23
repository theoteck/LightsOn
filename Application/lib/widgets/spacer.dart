// Import the material design widgets
import 'package:flutter/material.dart';

//::CustomSpacer::
//  Pretty simple, used to create space between two other widgets
class CustomSpacer extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Align(
        child: Container(
      width: 200,
      height: 15,
    ));
  }
}

//::CustomSpacer1::
//  The same as the above widget only with more vertical space
//  Could be merged with a constructor parameter
class CustomSpacer1 extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Align(
        child: Container(
      width: 200,
      height: 45,
    ));
  }
}
