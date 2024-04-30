pipeline {
    agent any
    stages {
        stage('Project linter') {
            steps {
                sh 'docker run --rm -v "$PWD:/mnt/delivery" ghcr.io/epitech/coding-style-checker:latest /mnt/delivery /mnt/reports'
            }
        }

        stage('Project compilation') {
            agent {
                docker { image 'epitechcontent/epitest-docker' }
            }
            steps {
                sh 'make clean'
                sh 'make'
                sh 'make fclean'
            }
        }

        stage('Project tests') {
            agent {
                docker { image 'epitechcontent/epitest-docker' }
            }
            steps {
                sh 'make tests_run'
            }
        }
    }
}
