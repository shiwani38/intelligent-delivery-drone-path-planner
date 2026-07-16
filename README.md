# intelligent-delivery-drone-path-planner
The "Intelligent Delivery Drone Path Planner" is a navigation system designed to compute safe and optimal delivery routes for autonomous drones. As drone delivery becomes common for e-commerce, medical supplies, and food delivery, drones must operate in complex environments with buildings and restricted airspace.
The system consists of 4 main modules: Airspace Map for environment representation, Route Planner for path computation, Drone Control for path following, and Flight Simulator for visualization.
Dijkstra’s Algorithm is used to find the shortest and safest path by assigning higher costs to restricted zones, thus minimizing both delivery time and risk.
