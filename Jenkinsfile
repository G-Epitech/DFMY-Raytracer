pipeline {
    agent none
    stages {
        stage('Project linter') {
            agent {
                docker { image 'ghcr.io/epitech/coding-style-checker:latest' }
            }
            steps {
                sh 'check.sh $(pwd) $(pwd)'
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
