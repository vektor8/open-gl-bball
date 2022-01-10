#include "Camera.hpp"

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {

        //TODO - Update the rest of camera parameters
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;
        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraFrontDirection, this->cameraUpDirection));

    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(cameraPosition, cameraPosition + cameraFrontDirection, cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {

        //TODO
        switch (direction)
        {
        case MOVE_FORWARD:
            //this->cameraPosition += speed * this->cameraFrontDirection;
            this->cameraPosition += speed * glm::vec3(this->cameraFrontDirection.x, 0.0f, this->cameraFrontDirection.z);
            break;
        case MOVE_BACKWARD:
            //this->cameraPosition -= speed * this->cameraFrontDirection;
            this->cameraPosition -= speed * glm::vec3(this->cameraFrontDirection.x, 0.0f, this->cameraFrontDirection.z);
            break;
        case MOVE_LEFT:
            this->cameraPosition -= speed * this->cameraRightDirection;
            //this->cameraPosition -= speed * glm::vec3(this->cameraRightDirection.x, 0.0f, this->cameraRightDirection.z);
            break;
        case MOVE_RIGHT:
            this->cameraPosition += speed * this->cameraRightDirection;
            //this->cameraPosition += speed * glm::vec3(this->cameraRightDirection.x, 0.0f, this->cameraRightDirection.z);
            break;
        default:
            break;
        }
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {
        //TODO
        this->cameraFrontDirection = glm::vec3(
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
            sin(glm::radians(pitch)),
            sin(glm::radians(yaw)) * cos(glm::radians(pitch))
        );

        this->cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, cameraUpDirection));
    }
}