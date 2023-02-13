#include "Camera.hpp"

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;
        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = -glm::normalize(glm::cross(cameraUp, cameraFrontDirection));
        this->originalUp = cameraUp;
        this->originalFront = cameraFrontDirection;
    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(cameraPosition, cameraTarget, cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        //TODO
        if (direction == MOVE_FORWARD) {
            cameraPosition = cameraPosition + speed * cameraFrontDirection;
        }

        if (direction == MOVE_BACKWARD) {
            cameraPosition = cameraPosition + speed * -cameraFrontDirection;
        }

        if (direction == MOVE_LEFT) {
            cameraPosition = cameraPosition + speed * -cameraRightDirection;
        }

        if (direction == MOVE_RIGHT) {
            cameraPosition = cameraPosition + speed * cameraRightDirection;
        }
        /*cameraTarget = normalize((cameraPosition + cameraOrigFront));*/
        cameraTarget = cameraPosition + cameraFrontDirection;
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {
        //TODO
        glm::mat4 euler = glm::yawPitchRoll(glm::radians(yaw), glm::radians(pitch), 0.0f);

        cameraFrontDirection = glm::vec3(glm::normalize((euler * glm::vec4(originalFront, 0.0f))));
        cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, originalUp));
        cameraUpDirection = glm::cross(cameraRightDirection, cameraFrontDirection);
        cameraTarget = cameraPosition + cameraFrontDirection;
    }
}