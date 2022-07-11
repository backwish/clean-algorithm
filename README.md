# 읽기 쉬운 알고리즘 문제 구현

# 소개
본 저장소는 많은 사람들이 해결한 알고리즘 문제를 중심으로 읽기 쉬운 코드를 작성하는 것을 목표로 하고 있습니다.
AC 받고 버려지는 것이 아닌 코드 리팩터링을 수행하면서 달성하려는 목표는 다음과 같습니다.

제작자는 클린 코드를 습관화하고, 새로운 알고리즘과 문제 해결 방법을 더 깊이 이해합니다. 
독자는 난해한 코드 해독이 아닌 다른 사람의 코드로 문제 해결하는 과정을 접하는데 더 집중할 수 있도록 합니다.

알고리즘 문제는 제한된 시간에 복잡도가 높은 문제를 해결해야 합니다. 그러므로, 문제를 처음 풀 때 완성된 코드가 나오는 것은 아주 어렵다고 생각합니다.
따라서, 제작자도 문제를 처음 풀 때부터 완성된 코드를 만드는 접근이 아닌, 문제 해결 후 리팩터링을 거치는 방법을 채택했습니다.


제가 작성한 다음 글은 본 프로젝트의 의의에 대해서 설명하고 있습니다.
[프로그래밍 패러다임에서 배우는 코딩 테스트](https://blog.naver.com/PostList.naver?blogId=doinglove1)

# 구성

코드는 모두 C++로 작성되어 있습니다. 추후 Java코드도 작성할 예정입니다.

# 가정
구현을 통한 문제 해결 과정 제시라는 목적을 위해 코드 전체적으로 다음과 같은 가정을 합니다.
1. 클래스 하나로 구현할 수 있는 문제인 경우, 하나의 클래스를 구성하는 대신에 전역 변수를 사용합니다.
2. 클래스가 아닌 struct를 사용합니다.
3. setter 사용은 최대한 지양하지만, setter를 꼭 사용하게 될 경우 setter 사용보다는 직접 접근을 합니다.
