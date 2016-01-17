
//
// Is bridging a Swift class to Qt possible? We need to
// iterate over the properties and get types and names.
//
// Preliminary conclusion: This is hard without subclassing from
// NSObject.
// 

class Foo {
    var name: String?
    var age: Int?
    
    func sayHello() {
        print("Hello to you, " + name!)
    }
}

let foo = Foo()
foo.name = "Bar"
foo.sayHello();

let mirror = Mirror(reflecting: foo)
print ("DisplayStyle:", mirror.displayStyle!)
print ("SubjectType", mirror.subjectType)

for case let (label?, value) in mirror.children {
    print ("Label:", label, "Value:", value)
    // ### But what about the property type?
}
print(String(Foo.self))
print(String(foo.name.dynamicType))


